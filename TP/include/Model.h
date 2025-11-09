#ifndef MODEL_H
#define MODEL_H

struct Coordenada {
    double x, y;
};

struct Demanda;
struct Parada;
struct Trecho;
struct Corrida;
struct Evento;

double calcularDistancia(Coordenada c1, Coordenada c2);

struct Demanda {
    int id;
    int tempo;
    Coordenada origem;
    Coordenada destino;
    int estado;
};

struct Parada {
    Coordenada coords;
    int tipo;
    int idDemanda;

    Parada(Coordenada c, int t, int id) : coords(c), tipo(t), idDemanda(id) {}
};

struct Trecho {
    Parada* p1;
    Parada* p2;
    double distancia;
    double tempo;
    int tipo;

    Trecho(Parada* p1_in, Parada* p2_in, double dist, double t, int tipo_in)
        : p1(p1_in), p2(p2_in), distancia(dist), tempo(t), tipo(tipo_in) {}
};

struct Evento {
    double tempo;
    Corrida* corrida;
    int indiceProximaParada;
};

#endif