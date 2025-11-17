#ifndef TADS_H
#define TADS_H

#include "Model.h"

// ===================================================================
// --- Listas Dinâmicas (Baseadas em Array) ---
// ===================================================================

/**
 * Classe base para as Listas.
 * Define a interface comum (capacidade, tamanho).
 * (Implementação manual de lista necessária pela restrição de não usar STL).
 */
class ListaBase {
protected:
    int capacidade;
    int tamanho;
    // 'redimensiona' é virtual puro, forçando as classes filhas a implementá-lo.
    virtual void redimensiona() = 0;

public:
    ListaBase();
    int getTamanho();
    bool estaVazia();
};

/**
 * Lista dinâmica especializada para armazenar inteiros (int).
 */
class ListaInt : public ListaBase {
private:
    int* dados;
    void redimensiona() override;

public:
    ListaInt();
    ~ListaInt();
    void insere(int item);
    int get(int i); // [ROBUSTO] Agora verifica o índice
    void removeUltimo();
    void limpa();
};

/**
 * Lista dinâmica especializada para ponteiros de Demanda (Demanda*).
 */
class ListaDemandaPtr : public ListaBase {
private:
    Demanda** dados;
    void redimensiona() override;

public:
    ListaDemandaPtr();
    ~ListaDemandaPtr();
    void insere(Demanda* item);
    Demanda* get(int i); // [ROBUSTO] Agora verifica o índice
    void set(int i, Demanda* item); // [ROBUSTO] Agora verifica o índice
    void limpa(bool deletaPonteiros);
};

/**
 * Lista dinâmica especializada para ponteiros de Parada (Parada*).
 */
class ListaParadaPtr : public ListaBase {
private:
    Parada** dados;
    void redimensiona() override;

public:
    ListaParadaPtr();
    ~ListaParadaPtr();
    void insere(Parada* item);
    Parada* get(int i); // [ROBUSTO] Agora verifica o índice
    void limpa(bool deletaPonteiros);
};

/**
 * Lista dinâmica especializada para ponteiros de Trecho (Trecho*).
 */
class ListaTrechoPtr : public ListaBase {
private:
    Trecho** dados;
    void redimensiona() override;

public:
    ListaTrechoPtr();
    ~ListaTrechoPtr();
    void insere(Trecho* item);
    Trecho* get(int i); // [ROBUSTO] Agora verifica o índice
    void limpa(bool deletaPonteiros);
};

/**
 * Lista dinâmica especializada para ponteiros de Evento (Evento*).
 * Usada como o array base para o MinHeap.
 */
class ListaEventoPtr : public ListaBase {
private:
    Evento** dados;
    void redimensiona() override;

public:
    ListaEventoPtr();
    ~ListaEventoPtr();
    void insere(Evento* item);
    Evento* get(int i); // [ROBUSTO] Agora verifica o índice
    void set(int i, Evento* item); // [ROBUSTO] Agora verifica o índice
    void removeUltimo(); // Usado pelo MinHeap para remoção
    void limpa(bool deletaPonteiros);
};

/**
 * Lista dinâmica especializada para ponteiros de Corrida (Corrida*).
 */
class ListaCorridaPtr : public ListaBase {
private:
    Corrida** dados;
    void redimensiona() override;

public:
    ListaCorridaPtr();
    ~ListaCorridaPtr();
    void insere(Corrida* item);
    Corrida* get(int i); // [ROBUSTO] Agora verifica o índice
    void limpa(bool deletaPonteiros);
};

// ===================================================================
// --- TADs Complexos (Corrida, MinHeap, Simulador) ---
// ===================================================================

/**
 * Estrutura que agrega todas as informações de uma Corrida.
 * Contém as listas de demandas, paradas e trechos que a compõem.
 */
struct Corrida {
    ListaInt idsDemandas;
    ListaParadaPtr paradas;
    ListaTrechoPtr trechos;

    double distanciaTotal;
    double somaDistIndividual;

    Corrida();
    ~Corrida();
    void limpa(); // Libera a memória das listas internas
};

/**
 * TAD MinHeap (Heap Binário Mínimo).
 * Usado como Fila de Prioridade para o Escalonador de Eventos.
 * A prioridade é o 'tempo' do Evento (quanto menor, mais prioritário).
 */
class MinHeap {
private:
    ListaEventoPtr heap; // Usa a Lista customizada como array base

    // Funções auxiliares para navegação na árvore
    int pai(int i);
    int esq(int i);
    int dir(int i);

    // Funções para manter a propriedade do heap
    void troca(int i, int j);
    void heapifyUp(int i);   // Corrige o heap "subindo" (bubble-up)
    void heapifyDown(int i); // Corrige o heap "descendo" (bubble-down)

public:
    MinHeap();
    ~MinHeap();

    void insere(Evento* e);     // Insere um novo evento O(log N)
    Evento* retiraProximo();  // Remove o evento de menor tempo O(log N)
    bool estaVazio();
    void finaliza();          // Limpa a memória do heap
};

/**
 * Classe principal que encapsula todo o estado e a lógica
 * da Simulação de Eventos Discretos (SED).
 */
class Simulador {
public:
    // Parâmetros de simulação lidos da entrada
    int eta;
    double gama;
    double delta;
    double alfa;
    double beta;
    double lambda;

    // Estruturas de dados centrais
    ListaDemandaPtr demandas; // Lista mestra de todas as demandas
    ListaCorridaPtr corridas; // Lista de todas as corridas geradas

private:
    MinHeap escalonador;    // O escalonador de eventos (fila de prioridade)
    double relogio;         // O tempo atual da simulação

public:
    Simulador();
    ~Simulador();

    // --- Fases Principais ---
    
    // Fase 1: Agrupamento
    void combinarCorridas();
    
    // Fase 2: Simulação
    void simular();

    // --- Funções Auxiliares ---

    // Usada na Fase 1 para checar os critérios (alfa, beta, lambda)
    bool validarCombinacao(Corrida* proposta, Demanda* novaDemanda);
    
    // Usada na Fase 1 para montar a rota da corrida
    void construirRota(Corrida* r);

    // Usada na Fase 2 para processar eventos do heap
    void processarEvento(Evento* e);
    
    // Usada na Fase 2 para imprimir a saída
    void gerarEstatisticas(Corrida* r, double tempoFinal);
    
    // Usada no final da Fase 1 para iniciar a simulação
    void agendarPrimeiroEvento(Corrida* r);
};

#endif