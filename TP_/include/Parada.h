#ifndef PARADA_H
#define PARADA_H

#include "Coordenada.h"

// Encaminhar declaração para evitar inclusão circular
class Demanda; 

// Tipo da parada
enum TipoParada {
    EMBARQUE,
    DESEMBARQUE
};

class Parada {
public:
    Coordenada localizacao;
    TipoParada tipo;
    Demanda* passageiro; // Referência à demanda (passageiro)

    // Construtor padrão (necessário para a ListaParada)
    Parada();

    /**
     * Construtor da Parada.
     */
    Parada(Coordenada loc, TipoParada tipo, Demanda* passageiro);
};

#endif // PARADA_H