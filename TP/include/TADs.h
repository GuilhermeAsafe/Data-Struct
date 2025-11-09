#ifndef TADS_H
#define TADS_H

#include "Model.h"

class ListaBase {
protected:
    int capacidade;
    int tamanho;
public:
    ListaBase();
    int getTamanho();
    bool estaVazia();
};

class ListaInt : public ListaBase {
private:
    int* dados;
    void redimensiona();
public:
    ListaInt();
    ~ListaInt();
    void insere(int item);
    int get(int i);
    void removeUltimo();
    void limpa();
};

class ListaDemandaPtr : public ListaBase {
private:
    Demanda** dados;
    void redimensiona();
public:
    ListaDemandaPtr();
    ~ListaDemandaPtr();
    void insere(Demanda* item);
    Demanda* get(int i);
    void set(int i, Demanda* item);
    void limpa(bool deletaPonteiros);
};

class ListaParadaPtr : public ListaBase {
private:
    Parada** dados;
    void redimensiona();
public:
    ListaParadaPtr();
    ~ListaParadaPtr();
    void insere(Parada* item);
    Parada* get(int i);
    void limpa(bool deletaPonteiros);
};

class ListaTrechoPtr : public ListaBase {
private:
    Trecho** dados;
    void redimensiona();
public:
    ListaTrechoPtr();
    ~ListaTrechoPtr();
    void insere(Trecho* item);
    Trecho* get(int i);
    void limpa(bool deletaPonteiros);
};

class ListaEventoPtr : public ListaBase {
private:
    Evento** dados;
    void redimensiona();
public:
    ListaEventoPtr();
    ~ListaEventoPtr();
    void insere(Evento* item);
    Evento* get(int i);
    void set(int i, Evento* item);
    void removeUltimo(); // CORREÇÃO
    void limpa(bool deletaPonteiros);
};

class ListaCorridaPtr : public ListaBase {
private:
    Corrida** dados;
    void redimensiona();
public:
    ListaCorridaPtr();
    ~ListaCorridaPtr();
    void insere(Corrida* item);
    Corrida* get(int i);
    void limpa(bool deletaPonteiros);
};

struct Corrida {
    ListaInt idsDemandas;
    ListaParadaPtr paradas;
    ListaTrechoPtr trechos;
    
    double distanciaTotal;
    double somaDistIndividual;

    Corrida();
    ~Corrida();
    void limpa();
};

class MinHeap {
private:
    ListaEventoPtr heap;

    int pai(int i);
    int esq(int i);
    int dir(int i);
    void troca(int i, int j);
    void heapifyUp(int i);
    void heapifyDown(int i);

public:
    MinHeap();
    ~MinHeap();

    void insere(Evento* e);
    Evento* retiraProximo();
    bool estaVazio();
    void finaliza();
};

class Simulador {
public:
    int eta;
    double gama;
    double delta;
    double alfa;
    double beta;
    double lambda;

    ListaDemandaPtr demandas;
    ListaCorridaPtr corridas;

private:
    MinHeap escalonador;
    double relogio;

public:
    Simulador();
    ~Simulador();
    
    void combinarCorridas();
    void simular();
    void run();

private:
    void construirRota(Corrida* r, ListaInt& indicesDemandas);
    void processarEvento(Evento* e);
    void gerarEstatisticas(Corrida* r, double tempoConclusao);
};

#endif