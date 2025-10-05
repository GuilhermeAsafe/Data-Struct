#include <iostream>
#include <sstream> // Inclua para std::stringstream
#include <string>
#include <stdexcept> // Útil para lidar com exceções de busca

// Supondo que você tenha esses includes:
#include "include/objeto.hpp"
#include "include/lista.hpp"
#include "include/movimento.hpp"
 
using namespace std;


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

        // 3. Verifica o ID lido e processa
        if(id == 'O'){
            // A leitura é em float, mas o construtor espera int, C++ fará a coerção (cast implícito)
            float centro_objeto, x, y, largura;
            
            if (ss >> centro_objeto >> x >> y >> largura) {
                // Passa float; C++ converte para os int's esperados pelo construtor de objetos
                objetos novo_objeto(id, centro_objeto, x, y, largura); 
                minha_lista.insert(novo_objeto);
            } else {
                 std::cerr << "Erro de formato na linha de objeto (O): faltando valores numéricos." << std::endl;
            }
        }

        // 4. COMANDO 'M' (Movimento)
        else if(id == 'M'){ // M <tempo> <objeto> <x> <y>.
            float tempo;
            float objeto_busca, x_atualizado, y_atualizado;

            if (ss >> tempo >> objeto_busca >> x_atualizado >> y_atualizado) {
                movimento novo_movimento(id, tempo, objeto_busca, x_atualizado, y_atualizado);
                
                // Chamada CORRIGIDA: passando a lista e os dados de movimento.
                novo_movimento.movimentar(minha_lista);
            } else {
                std::cerr << "Erro de formato na linha de movimento (M): faltando valores numéricos." << std::endl;
            }
        } 
        
        // 5. COMANDO 'C' (Cena) - Ação que dispara a ordenação
        else if(id == 'C'){ // C <tempo>
            float tempo;
            if (ss >> tempo) {
                
                // 1. ORDENAÇÃO da lista
                minha_lista.ordenaPorY();
                
                // 2. IMPRIME A LISTA ORDENADA (Solicitado pelo usuário)
                std::cout << "--- CENA GERADA (Ordenada por Y) no tempo: " << tempo << " ---" << std::endl;
                minha_lista.print();
                std::cout << "---------------------------------------------------" << std::endl;
                
                // [Aqui entraria a lógica final de detecção de oclusão para gerar o output 'S']
                
            } else {
                std::cerr << "Erro de formato na linha de cena (C): faltando tempo." << std::endl;
            }

        }
        
        // 6. COMANDO 'Q' (Quit)
        else if(id == 'Q'){
            break;
        }
    }

    // Impressão final (após o 'Q')
    minha_lista.print();

    return 0;
}