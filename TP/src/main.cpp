#include <iostream>
#include <sstream> // Inclua para std::stringstream
#include <string>

// Supondo que você tenha esses includes:
#include "include/objeto.hpp"
#include "include/lista.hpp"
#include "include/movimento.hpp"
 
using namespace std;


// É crucial que a sua classe 'objetos' use os tipos corretos
// baseados no que você está tentando ler.
// O seu código de parsing estava lendo 4 INTs:
/*
    int centro_objeto
    int x
    int y
    int largura
*/
// MAS, a inicialização dos seus objetos usa doubles:
// objetos obj1('O', 1.0, 2.0, 3.0, 4.0);

// Vou assumir que os dados devem ser LIDOS como INTEIROS,
// mas a solução com stringstream é flexível para usar 'double' se for o caso.


int main()
{
    listas minha_lista;
    string minhaString;

    
    // O loop while (getline(std::cin, minhaString)) está correto para leitura.
    while (getline(std::cin, minhaString))
    {
        // 1. Cria um stream a partir da linha
        std::stringstream ss(minhaString);
        
        char id;
        
        // 2. Tenta ler o primeiro caractere (ID)
        if (!(ss >> id)) {
            // Se falhar a leitura do ID (linha vazia, etc.), continua para a próxima
            continue;
        }

        // 3. Verifica o ID lido
        if(id == 'O'){
            // Declare as variáveis no tipo que você deseja extrair.
            // Vou usar 'int' baseado no seu código de parsing original.
            float centro_objeto, x, y, largura;
            
            // 4. Usa o stream para ler os 4 inteiros em sequência, ignorando espaços.
            // O operador '>>' move automaticamente para o próximo campo.
            if (ss >> centro_objeto >> x >> y >> largura) {
                // Se TODOS os 4 valores forem lidos com sucesso
                
                // NOTA: Se o construtor de 'objetos' for 'objetos(char, double, double, double, double)',
                // o compilador fará a conversão implícita de int para double. 
                objetos novo_objeto(id, centro_objeto, x, y, largura);
                minha_lista.insert(novo_objeto);
            } else {
                 std::cerr << "Erro de formato na linha de objeto (O): faltando valores numéricos." << std::endl;
            }
        }

        else if(id == 'M'){ //M <tempo> <objeto> <x> <y>.
            float tempo;
            float objeto_busca, x_atualizado, y_atualizado;

            if (ss >> tempo >> objeto_busca>> x_atualizado >> y_atualizado) {
                movimento novo_movimento(id, tempo, objeto_busca, x_atualizado, y_atualizado);
                novo_movimento.movimentar(minha_lista, objeto_busca);
            } else {
                 std::cerr << "Erro de formato na linha de movimento (M): faltando valores numéricos." << std::endl;
        }

        } else if(id == 'Q'){
            // O comando 'Q' deve ser verificado com o ID lido
            break;
        }

        // NÃO é necessário chamar minhaString.clear() aqui, pois getline()
        // já sobrescreve o conteúdo na próxima iteração.
    }

 

    minha_lista.print();

    return 0;
}