#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <cmath>     // Para Coordenada
#include <stdexcept> // Para Listas e MinHeap

// --- Declarações Encaminhadas (Forward Declarations) ---
class Demanda;
class Parada;
class Trecho;
class Evento;
class Corrida;

// --- Coordenada.h ---
struct Coordenada {
    double x; 
    double y; 
    Coordenada(double x_val = 0.0, double y_val = 0.0); 
    double distancia(const Coordenada& outra) const;
};

// --- Demanda.h ---
enum EstadoDemanda { DEMANDADA, INDIVIDUAL, COMBINADA, CONCLUIDA };
class Demanda {
public:
    int id;
    int tempo;
    Coordenada origem;
    Coordenada destino;
    EstadoDemanda estado;
    Demanda(int id, int tempo, Coordenada origem, Coordenada destino);
    double getDistanciaIdeal() const;
};

// --- Parada.h ---
enum TipoParada { EMBARQUE, DESEMBARQUE };
class Parada {
public:
    Coordenada localizacao;
    TipoParada tipo;
    Demanda* passageiro; 
    Parada();
    Parada(Coordenada loc, TipoParada tipo, Demanda* passageiro);
};

// --- Trecho.h ---
enum TipoTrecho { COLETA, ENTREGA, DESLOCAMENTO };
class Trecho {
public:
    Parada* paradaOrigem;
    Parada* paradaDestino;
    double distancia;
    double tempoGasto;
    TipoTrecho natureza;
    Trecho(); 
    Trecho(Parada* origem, Parada* destino, double gama_velocidade);
    void definirNatureza();
};

// --- Evento.h ---
enum TipoEvento { CHEGADA_PARADA };
class Evento {
public:
    double tempo;
    TipoEvento tipo;
    Corrida* corrida;
    int indiceTrecho;
    Evento(double t, TipoEvento tp, Corrida* c, int indice);
    bool operator>(const Evento& outro) const;
};

// --- ListaDemanda.h ---
struct NoDemanda {
    Demanda* dado;
    NoDemanda* proximo;
    NoDemanda(Demanda* d);
};
class ListaDemanda {
private:
    NoDemanda* inicio;
    NoDemanda* fim;
    int tamanho;
public:
    ListaDemanda();
    ~ListaDemanda();
    void push_back(Demanda* d);
    Demanda* get(int index);
    Demanda* pop_back();
    int size() const;
    bool empty() const;
    void clear(); 
};

// --- ListaParada.h ---
struct NoParada {
    Parada dado;
    NoParada* proximo;
    NoParada(Parada p);
};
class ListaParada {
private:
    NoParada* inicio;
    NoParada* fim;
    int tamanho;
public:
    ListaParada();
    ~ListaParada();
    void push_back(Parada p);
    Parada* get(int index);
    int size() const;
    bool empty() const;
    void clear();
};

// --- ListaTrecho.h ---
struct NoTrecho {
    Trecho dado;
    NoTrecho* proximo;
    NoTrecho(Trecho t);
};
class ListaTrecho {
private:
    NoTrecho* inicio;
    NoTrecho* fim; 
    int tamanho;
public:
    ListaTrecho();
    ~ListaTrecho();
    void push_back(Trecho t);
    Trecho& get(int index);
    int size() const;
    bool empty() const;
    void clear(); 
};

// --- ListaCorrida.h ---
struct NoCorrida {
    Corrida* dado;
    NoCorrida* proximo;
    NoCorrida(Corrida* c);
};
class ListaCorrida {
private:
    NoCorrida* inicio;
    NoCorrida* fim;
    int tamanho;
public:
    ListaCorrida();
    ~ListaCorrida();
    void push_back(Corrida* c);
    Corrida* get(int index);
    int size() const;
    bool empty() const;
    void clear(); 
};

// --- Corrida.h ---
class Corrida {
private:
    double gama_velocidade;
    void reconstruirRota();
public:
    ListaDemanda demandasAtendidas;
    ListaTrecho trechos;
    ListaParada paradas;
    double distanciaTotal;
    double tempoTotal;
    double eficiencia;
    int numeroParadas;
    Corrida(double gama);
    ~Corrida();
    void adicionarDemanda(Demanda* demanda);
    void removerUltimaDemanda();
    void calcularEficiencia();
};

// --- MinHeap.h ---
class MinHeap {
private:
    Evento** dados;
    int capacidade;
    int tamanho;
    void redimensionar();
    void heapifyUp(int index);
    void heapifyDown(int index);
    void swap(int i, int j);
    int getParent(int i) { return (i - 1) / 2; }
    int getLeftChild(int i) { return 2 * i + 1; }
    int getRightChild(int i) { return 2 * i + 2; }
public:
    MinHeap();
    ~MinHeap();
    void inserir(Evento* evento);
    Evento* removerMin();
    bool estaVazio() const;
};

#endif // ESTRUTURAS_H