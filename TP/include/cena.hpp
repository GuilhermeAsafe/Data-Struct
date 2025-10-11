#ifndef CENA_HPP
#define CENA_HPP

#include "include/lista.hpp" // Para acessar 'objetos'

class Cena
{
public:
    // Estrutura para armazenar um segmento visível (corresponde à linha de saída 'S')
    struct Segmento
    {
        int tempo;
        double id_objeto;
        double inicio;
        double fim;
        Segmento* prox;

        Segmento(int t, double id, double i, double f) : 
            tempo(t), id_objeto(id), inicio(i), fim(f), prox(nullptr) {}
    };

    // Lista encadeada para armazenar todos os segmentos visíveis gerados
    Segmento* head = nullptr;
    Segmento* tail = nullptr;

    // Função interna para inserir um novo segmento no final da lista
    void insereSegmento(int tempo, double id, double inicio, double fim);
    
    // Estrutura auxiliar para rastrear oclusão (Lista de Intervalos Ocupados)
      struct IntervaloOcupado 
    {
        double inicio;
        double fim;
        IntervaloOcupado* prox;
        
        IntervaloOcupado(double i, double f) : inicio(i), fim(f), prox(nullptr) {}
    };

    // Função auxiliar para inserir/unir intervalos ocupados na lista de oclusão.
    void adicionaIntervaloOcupado(IntervaloOcupado** head_ref, double inicio, double fim);

     // --- MÉTODOS AUXILIARES PARA ORDENAÇÃO DA SAÍDA (Por id_objeto) ---
    Segmento* getMiddleSegmentos(Segmento* head);
    Segmento* mergeSegmentos(Segmento* a, Segmento* b);
    Segmento* mergeSortSegmentos(Segmento* head);

public:

    Cena() = default;
    ~Cena(); // Destrutor para liberar a memória dos segmentos

    // NOVO: Getter para o head da lista de segmentos
    Segmento* getHeadSegmentos() const { return head; } // <-- Adicione este método

    // Método principal para processar a lista e gerar a cena no tempo 'tempo_cena'
    void processaCena(listas& lista_objetos, double tempo_cena);

    void resetSegmentos() {
        head = nullptr;
        tail = nullptr;
    }


    // Método para imprimir a cena final no formato 'S'
    void gravaCena();
};

#endif 
