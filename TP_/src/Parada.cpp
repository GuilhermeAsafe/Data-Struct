#include "Parada.h"
#include "Demanda.h" // Inclui a definição completa

// Construtor padrão
Parada::Parada()
    : localizacao(0, 0), tipo(EMBARQUE), passageiro(nullptr)
{
    // Construtor
}

Parada::Parada(Coordenada loc, TipoParada tipo, Demanda* passageiro)
    : localizacao(loc), tipo(tipo), passageiro(passageiro) 
{
    // Construtor
}