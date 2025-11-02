#include "Parada.h"
#include "Demanda.h" // Inclui a definição completa de Demanda

Parada::Parada(Coordenada loc, TipoParada tipo, Demanda* passageiro)
    : localizacao(loc), tipo(tipo), passageiro(passageiro) 
{
    // Construtor
}