#include "Demanda.h"

Demanda::Demanda(int id, int tempo, Coordenada origem, Coordenada destino)
    : id(id), 
      tempo(tempo), 
      origem(origem), 
      destino(destino), 
      estado(DEMANDADA) 
{
    // Construtor
}

double Demanda::getDistanciaIdeal() const {
    return this->origem.distancia(this->destino);
}