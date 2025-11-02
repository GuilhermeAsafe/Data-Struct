#ifndef TRECHO_H
#define TRECHO_H

#include "Parada.h"

// Natureza do trecho
enum TipoTrecho {
    COLETA,
    ENTREGA,
    DESLOCAMENTO
};

class Trecho {
public:
    Parada* paradaOrigem;
    Parada* paradaDestino;
    double distancia;
    double tempoGasto;
    TipoTrecho natureza;

    // Construtor padrão (necessário para a ListaTrecho)
    Trecho(); 

    /**
     * Construtor do Trecho.
     * 'gama' (velocidade) é necessário para calcular o tempoGasto.
     */
    Trecho(Parada* origem, Parada* destino, double gama_velocidade);

    /**
     * Define a natureza do trecho baseado nas paradas.
     */
    void definirNatureza();
};

#endif // TRECHO_H