#ifndef MODEL_H
#define MODEL_H

// Estrutura simples para guardar coordenadas X e Y
struct Coordenada {
    double x, y;
};

// --- Declarações (forward declarations) ---
// Permitem que as estruturas abaixo se refiram umas às outras
// sem problemas de ordem de inclusão.
struct Demanda;
struct Parada;
struct Trecho;
struct Corrida;
struct Evento;

// Função auxiliar para calcular a distância entre dois pontos
double calcularDistancia(Coordenada c1, Coordenada c2);

// Estrutura que representa um pedido de viagem (uma demanda)
struct Demanda {
    int id;
    int tempo; // Instante em que a demanda foi criada
    Coordenada origem;
    Coordenada destino;
    int estado; // 0=livre, 1=agrupada, 2=coletada, 3=finalizada, 4=atendida
};

// Estrutura que representa um ponto de parada (coleta ou entrega)
struct Parada {
    Coordenada coords;
    int tipo; // 0 para coleta, 1 para entrega
    int idDemanda; // ID da demanda associada a esta parada

    // Construtor para facilitar a criação
    Parada(Coordenada c, int t, int id) : coords(c), tipo(t), idDemanda(id) {}
};

// Estrutura que representa o caminho entre duas paradas
struct Trecho {
    Parada* p1;
    Parada* p2;
    double distancia;
    double tempo;
    int tipo; // 0 para coleta, 1 para entrega

    // Construtor
    Trecho(Parada* p1_in, Parada* p2_in, double dist, double t, int tipo_in)
        : p1(p1_in), p2(p2_in), distancia(dist), tempo(t), tipo(tipo_in) {}
};

// Estrutura que representa um evento na fila de prioridade (MinHeap)
// Basicamente, é a "chegada" a uma parada.
struct Evento {
    double tempo; // O "tempo" do evento (chave do heap)
    Corrida* corrida;
    int indiceProximaParada; // Índice da parada na lista de paradas da corrida
};

#endif