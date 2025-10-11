#include <iostream>
#include <sstream> 
#include <string>  
#include <stdexcept> 
#include <iomanip> // NECESSÁRIO para a formatação de double
#include <fstream> // NOVO: Necessário para manipulação de arquivos

// Supondo que você tenha esses includes:
#include "include/objeto.hpp"
#include "include/lista.hpp"
#include "include/movimento.hpp"
#include "include/cena.hpp" 

using namespace std;

// ==========================================================
// NOVO: LISTA ENCADEADA PARA ARMAZENAR A SAÍDA FINAL (print_final)
// Esta lista armazena os DADOS brutos para a impressão final.
// ==========================================================
class SaidaFinal {
private:
    // Estrutura para armazenar os DADOS de cada linha 'S'
    struct SegmentoSaida {
        int tempo;
        // O id_objeto é double na classe objetos, mas é inteiro na saída ('S 6 0...')
        int id_objeto; 
        double inicio;
        double fim;
        SegmentoSaida* prox;
        
        // Construtor para armazenar os dados crus
        SegmentoSaida(int t, int id, double i, double f) 
            : tempo(t), id_objeto(id), inicio(i), fim(f), prox(nullptr) {}
    };
    SegmentoSaida* head = nullptr;
    SegmentoSaida* tail = nullptr;

public:
    // Destrutor para liberar a memória
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

     // Imprime todos os conteúdos acumulados na ordem, aplicando a formatação
    void imprime() const {
        // Configura a formatação para 2 casas decimais.
        std::cout << std::fixed << std::setprecision(2); 
        
        SegmentoSaida* current = head;
        while (current != nullptr) {
            // 1. Imprime os dados SEM QUEBRA DE LINHA NO FINAL
            std::cout << "S " 
                      << current->tempo << " " 
                      << current->id_objeto 
                      << " " << current->inicio 
                      << " " << current->fim; 
                      
            // 2. CRÍTICO: Imprime a quebra de linha (o separador) SOMENTE se houver um próximo elemento.
            if (current->prox != nullptr) {
                std::cout << std::endl; // Adiciona o \n de separação
            }

            current = current->prox;
        }
        
       // Reverte a formatação do stream
       std::cout << std::defaultfloat; 
    }
       
    };

int main() 
{
    // Declarações (listas, cena e variaveis de controle)
    listas minha_lista;
    string minhaString;
    Cena minha_cena;
    SaidaFinal print_final;

    #include "include/objeto.hpp"

objetos::objetos(char id , double centro_objeto , double x ,  double y , double largura)
{
    this->id = id;
    this->id_objeto = centro_objeto;
    this->x = x;
    this->y = y;
    this->largura = largura;
}

//objeto::objeto(char id , int centro_obeto , int x ,  int y , int largura) : 
//id(id), centro_obeto(centro_obeto), x(x), y(y), largura(largura) {}
        
        char id;
        
        // 2. Tenta ler o primeiro caractere (ID)
        if (!(ss >> id)) {
            // Se falhar a leitura do ID (linha vazia, etc.), continua para a próxima
            continue;
        }

        // 3. Verifica o ID lido e processa
        if(id == 'O'){
            double centro_objeto, x, y, largura;
            
            if (ss >> centro_objeto >> x >> y >> largura) {
                objetos novo_objeto(id, centro_objeto, x, y, largura); 
                minha_lista.insert(novo_objeto);
            } else {
                 std::cerr << "Erro de formato na linha de objeto (O): faltando valores numéricos." << std::endl;
            }
        }

        // 4. COMANDO 'M' (Movimento)
        else if(id == 'M'){ // M <tempo> <objeto> <x> <y>.
            double tempo;
            double objeto_busca, x_atualizado, y_atualizado;

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
            double tempo;
            if (ss >> tempo) {
                   
                // 1. ORDENAÇÃO da lista e PROCESSAMENTO (popula a lista interna de Cena)
                minha_lista.ordenaPorY();
                minha_cena.processaCena(minha_lista, tempo);
                
                // 2. GRAVAÇÃO/PREPARAÇÃO: Apenas ordena a lista INTERNA de Cena
                minha_cena.gravaCena();

                // 3. TRANSFERÊNCIA E LIMPEZA (Novo processo no main.cpp)
                Cena::Segmento* current_segmento = minha_cena.getHeadSegmentos();
                Cena::Segmento* next_segmento = nullptr;

                while(current_segmento != nullptr) {
                    // Insere os dados crus na lista de saída final
                    print_final.insere(
                        current_segmento->tempo,
                        (int)current_segmento->id_objeto, // Converte para int, como no output
                        current_segmento->inicio,
                        current_segmento->fim
                    );

                    // Deleta o nó e avança (limpa a memória da Cena)
                    next_segmento = current_segmento->prox;
                    delete current_segmento;
                    current_segmento = next_segmento;
                }
                
                // CORREÇÃO ESSENCIAL: Zera os ponteiros de Cena para evitar o double free no destrutor.
                minha_cena.resetSegmentos(); 
                
            } else {
                std::cerr << "Erro de formato na linha de cena (C): faltando tempo." << std::endl;
            }

        }
    }

    // IMPRESSÃO FINAL: Executada assim que o std::cin chega ao EOF.
    print_final.imprime(); 

    return 0;
}