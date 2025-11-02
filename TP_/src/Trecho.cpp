#include "Trecho.h"
#include <stdexcept> 

// Construtor padrão
Trecho::Trecho() 
    : paradaOrigem(nullptr), 
      paradaDestino(nullptr), 
      distancia(0.0), 
      tempoGasto(0.0), 
      natureza(DESLOCAMENTO) 
{}

Trecho::Trecho(Parada* origem, Parada* destino, double gama_velocidade)
    : paradaOrigem(origem), paradaDestino(destino) 
{
    if (paradaOrigem == nullptr || paradaDestino == nullptr) {
        throw std::invalid_argument("Paradas de origem ou destino não podem ser nulas.");
    }

    this->distancia = paradaOrigem->localizacao.distancia(paradaDestino->localizacao);

    if (gama_velocidade <= 0) {
        // Se a velocidade for 0, o tempo é "infinito"
        // Para evitar divisão por zero, definimos como 0
        this->tempoGasto = 0.0;
    } else {
        // Tempo = Distância / Velocidade
        this->tempoGasto = this->distancia / gama_velocidade;
    }

    definirNatureza();
}

void Trecho::definirNatureza() {
    // Define a natureza conforme a especificação
    if (paradaOrigem->tipo == EMBARQUE && paradaDestino->tipo == EMBARQUE) {
        this->natureza = COLETA;
    } else if (paradaOrigem->tipo == DESEMBARQUE && paradaDestino->tipo == DESEMBARQUE) {
        this->natureza = ENTREGA;
    } else {
        // Inclui EMBARQUE -> DESEMBARQUE
        this->natureza = DESLOCAMENTO;
    }
}