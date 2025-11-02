#include "Demanda.h"

Demanda::Demanda(int id, int tempo, Coordenada origem, Coordenada destino)
    : id(id), 
      tempo(tempo), 
      origem(origem), 
      destino(destino), 
      estado(DEMANDADA) // Toda demanda começa como "demandada"
{
    // Construtor inicializa os membros
}