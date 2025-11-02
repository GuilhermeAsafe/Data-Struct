#include "Corrida.h"

Corrida::Corrida()
    : distanciaTotal(0.0), 
      tempoTotal(0.0), 
      eficiencia(1.0), // Corrida individual tem 100% de eficiência
      numeroParadas(0)
{
    // Construtor
}

void Corrida::adicionarTrecho(Trecho trecho) {
    trechos.push_back(trecho); // A interface é a mesma
    this->distanciaTotal += trecho.distancia;
    this->tempoTotal += trecho.tempoGasto;
    this->numeroParadas = trechos.size() + 1; 
}

void Corrida::adicionarDemanda(Demanda* demanda, double gama) {
    demandasAtendidas.push_back(demanda);
    
    // --- TODO: LÓGICA DE RECONSTRUÇÃO DA ROTA ---
    // Esta é a parte complexa do trabalho.
    
    // 1. Limpar trechos antigos (agora funciona com a lista encadeada)
    trechos.clear();
    this->distanciaTotal = 0.0;
    this->tempoTotal = 0.0;
    this->numeroParadas = 0;

    // 2. Criar lista de Paradas
    //    (Na versão básica[cite: 922], a ordem é:
    //     Embarque c0, Embarque c1, ..., Desembarque c0, Desembarque c1, ...)
    
    // 3. Criar novos Trechos ligando as Paradas em sequência
    
    // 4. Chamar adicionarTrecho() para cada novo trecho
}

void Corrida::calcularEficiencia() {
    // --- TODO: LÓGICA DE CÁLCULO DE EFICIÊNCIA ---
    // Eficiência = (Soma das distâncias individuais) / (Distância total da rota)
    // [cite: 906, 911-912]
}