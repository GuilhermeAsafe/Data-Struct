#include "Evento.h"
#include "Corrida.h" // Inclui a definição completa

Evento::Evento(double t, TipoEvento tp, Corrida* c, int indice)
    : tempo(t), tipo(tp), corrida(c), indiceTrecho(indice) 
{
    // Construtor
}

bool Evento::operator>(const Evento& outro) const {
    // Compara pelo tempo. Essencial para o MinHeap.
    return this->tempo > outro.tempo;
}