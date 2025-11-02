#include "Trecho.h"
#include <stdexcept> // Para exceções

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

    // Calcula a distância usando a função da Coordenada
    this->distancia = paradaOrigem->localizacao.distancia(paradaDestino->localizacao);

    // Calcula o tempo gasto (Tempo = Distância / Velocidade) [cite: 895-896]
    if (gama_velocidade <= 0) {
        throw std::invalid_argument("Velocidade (gama) deve ser positiva.");
    }
    this->tempoGasto = this->distancia / gama_velocidade;

    // Define a natureza do trecho
    definirNatureza();
}

void Trecho::definirNatureza() {
    // Define a natureza conforme a especificação
    if (paradaOrigem->tipo == EMBARQUE && paradaDestino->tipo == EMBARQUE) {
        this->natureza = COLETA;
    } else if (paradaOrigem->tipo == DESEMBARQUE && paradaDestino->tipo == DESEMBARQUE) {
        this->natureza = ENTREGA;
    } else if (paradaOrigem->tipo == EMBARQUE && paradaDestino->tipo == DESEMBARQUE) {
        this->natureza = DESLOCAMENTO;
    } else {
        this->natureza = DESLOCAMENTO; 
    }
}