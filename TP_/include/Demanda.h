#ifndef DEMANDA_H
#define DEMANDA_H

#include "Coordenada.h"

// Estados possíveis de uma demanda
enum EstadoDemanda {
    DEMANDADA,
    INDIVIDUAL,
    COMBINADA,
    CONCLUIDA
};

class Demanda {
public:
    int id;
    int tempo;
    Coordenada origem;
    Coordenada destino;
    EstadoDemanda estado;

    /**
     * Construtor para inicializar uma demanda lida do arquivo.
     */
    Demanda(int id, int tempo, Coordenada origem, Coordenada destino);

    /**
     * Calcula a distância "ideal" (linha reta) desta demanda.
     */
    double getDistanciaIdeal() const;
};

#endif // DEMANDA_H