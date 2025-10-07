#ifndef CENA_HPP
#define CENA_HPP

#include "include/lista.hpp" // Para acessar 'objetos'

class Cena
{
private:
    // Estrutura para armazenar um segmento visível (corresponde à linha de saída 'S')
    struct Segmento
    {
        int tempo;
        float id_objeto;
        float inicio;
        float fim;
        Segmento* prox;

        Segmento(int t, float id, float i, float f) : 
            tempo(t), id_objeto(id), inicio(i), fim(f), prox(nullptr) {}
    };

    // Lista encadeada para armazenar todos os segmentos visíveis gerados
    Segmento* head = nullptr;
    Segmento* tail = nullptr;

    // Função interna para inserir um novo segmento no final da lista
    void insereSegmento(int tempo, float id, float inicio, float fim);
    
    // Estrutura auxiliar para rastrear oclusão (Lista de Intervalos Ocupados)
    struct IntervaloOcupado 
    {
        float inicio;
        float fim;
        IntervaloOcupado* prox;
        
        IntervaloOcupado(float i, float f) : inicio(i), fim(f), prox(nullptr) {}
    };

    // Função auxiliar para inserir/unir intervalos ocupados na lista de oclusão.
    void adicionaIntervaloOcupado(IntervaloOcupado** head_ref, float inicio, float fim);

     // --- MÉTODOS AUXILIARES PARA ORDENAÇÃO DA SAÍDA (Por id_objeto) ---
    Segmento* getMiddleSegmentos(Segmento* head);
    Segmento* mergeSegmentos(Segmento* a, Segmento* b);
    Segmento* mergeSortSegmentos(Segmento* head);

public:

    Cena() = default;
    ~Cena(); // Destrutor para liberar a memória dos segmentos

    // Método principal para processar a lista e gerar a cena no tempo 'tempo_cena'
    void processaCena(listas& lista_objetos, float tempo_cena);

    // Método para imprimir a cena final no formato 'S'
    void gravaCena();
};

#endif