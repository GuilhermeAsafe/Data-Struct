#include <iostream>
#include <sstream> 
#include <string>  
#include <stdexcept> 
#include <iomanip> // Necessário para std::fixed, std::setprecision, std::defaultfloat

// Includes das Classes TAD
#include "include/objeto.hpp"
#include "include/lista.hpp"
#include "include/movimento.hpp"
#include "include/cena.hpp" 

using namespace std;

// ==========================================================
// CLASSE: SaidaFinal
// Funcionalidade: Estrutura de dados (lista encadeada) para acumular
// e imprimir a saída final do programa, garantindo a ordem
// e o formato exato (precisão e quebras de linha).
// ==========================================================
class SaidaFinal {
private:
    // Estrutura do nó que armazena os dados de um segmento visível ('S')
    struct SegmentoSaida {
        int tempo;
        int id_objeto; 
        double inicio;
        double fim;
        SegmentoSaida* prox;
        
        // Construtor
        SegmentoSaida(int t, int id, double i, double f) 
            : tempo(t), id_objeto(id), inicio(i), fim(f), prox(nullptr) {}
    };
    SegmentoSaida* head = nullptr;
    SegmentoSaida* tail = nullptr;

public:
    // Destrutor: Libera a memória de todos os nós SegmentoSaida criados
    ~SaidaFinal() {
        SegmentoSaida* current = head;
        while (current != nullptr) {
            SegmentoSaida* next = current->prox;
            delete current;
            current = next;
        }
    }

    // Insere os dados crus no final da lista
    void insere(int tempo, int id, double inicio, double fim) {
        SegmentoSaida* novo = new SegmentoSaida(tempo, id, inicio, fim);
        if (head == nullptr) {
            head = novo;
            tail = novo;
        } else {
            tail->prox = novo;
            tail = novo;
        }
    }

    // Imprime toda a saída acumulada no formato exigido
    void imprime() const {
        // Configura a precisão de 2 casas decimais para o output
        std::cout << std::fixed << std::setprecision(2); 
        
        SegmentoSaida* current = head;
        while (current != nullptr) {
            // 1. Imprime os dados (sem quebra de linha no final desta linha)
            std::cout << "S " 
                      << current->tempo << " " 
                      << current->id_objeto 
                      << " " << current->inicio 
                      << " " << current->fim; 
                      
            // 2. Imprime a quebra de linha (separador) SOMENTE se não for a última linha.
            if (current->prox != nullptr) {
                std::cout << std::endl; 
            }

            current = current->prox;
        }
        
       // Reverte a formatação do stream para o padrão
       std::cout << std::defaultfloat; 
    }
};
// ==========================================================


// Função Principal
int main() 
{
    // Declarações das classes TAD e variáveis de controle
    listas minha_lista;
    string minhaString;
    Cena minha_cena;
    SaidaFinal print_final; // Lista para acumular a saída final

    
    // Loop principal: Lê linha por linha do Standard Input (std::cin).
    // O loop termina automaticamente ao atingir o Fim de Arquivo (EOF).
    while (getline(std::cin, minhaString))
    {
        // Cria um stream temporário para análise e leitura dos campos da linha
        std::stringstream ss(minhaString);
        
        char id;
        
        // Tenta ler o primeiro caractere (ID do comando)
        if (!(ss >> id)) {
            continue; // Pula linhas vazias ou inválidas
        }

        // --- COMANDO 'O' (Objeto) ---
        if(id == 'O'){
            double centro_objeto, x, y, largura;
            
            if (ss >> centro_objeto >> x >> y >> largura) {
                // Cria e insere o novo objeto na lista principal
                objetos novo_objeto(id, centro_objeto, x, y, largura); 
                minha_lista.insert(novo_objeto);
            } else {
                 std::cerr << "Erro de formato na linha de objeto (O): faltando valores numéricos." << std::endl;
            }
        }

        // --- COMANDO 'M' (Movimento) ---
        else if(id == 'M'){ 
            double tempo;
            double objeto_busca, x_atualizado, y_atualizado;

            if (ss >> tempo >> objeto_busca >> x_atualizado >> y_atualizado) {
                movimento novo_movimento(id, tempo, objeto_busca, x_atualizado, y_atualizado);
                
                // Atualiza as coordenadas do objeto na lista
                novo_movimento.movimentar(minha_lista);
            } else {
                std::cerr << "Erro de formato na linha de movimento (M): faltando valores numéricos." << std::endl;
            }
        } 
        
        // --- COMANDO 'C' (Cena - Processamento e Saída) ---
        else if(id == 'C'){ 
            double tempo;
            if (ss >> tempo) {
                   
                // 1. Prepara a cena: Ordena a lista por Y (distância) e detecta a oclusão
                minha_lista.ordenaPorY();
                minha_cena.processaCena(minha_lista, tempo);
                
                // 2. Ordena os segmentos visíveis gerados (por id_objeto)
                minha_cena.gravaCena();

                // 3. TRANSFERÊNCIA E LIMPEZA: Move os nós de Cena para a lista de Saída Final
                Cena::Segmento* current_segmento = minha_cena.getHeadSegmentos();
                Cena::Segmento* next_segmento = nullptr;

                while(current_segmento != nullptr) {
                    // Insere os dados na lista de saída final para impressão posterior
                    print_final.insere(
                        current_segmento->tempo,
                        (int)current_segmento->id_objeto, 
                        current_segmento->inicio,
                        current_segmento->fim
                    );

                    // Deleta o nó e avança (limpa a memória da Cena após o processamento)
                    next_segmento = current_segmento->prox;
                    delete current_segmento;
                    current_segmento = next_segmento;
                }
                
                // Zera os ponteiros head/tail da Cena. CRÍTICO para evitar o double free no destrutor de Cena.
                minha_cena.resetSegmentos(); 
                
            } else {
                std::cerr << "Erro de formato na linha de cena (C): faltando tempo." << std::endl;
            }
        }
    }

    // IMPRESSÃO FINAL: Executada após o término da entrada (EOF).
    print_final.imprime(); 

    return 0;
}