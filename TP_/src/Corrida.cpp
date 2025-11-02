#include "Corrida.h"

Corrida::Corrida(double gama)
    : gama_velocidade(gama),
      distanciaTotal(0.0), 
      tempoTotal(0.0), 
      eficiencia(1.0), 
      numeroParadas(0)
{
    // Construtor
}

Corrida::~Corrida() {
    // As listas de ponteiros (demandasAtendidas) são limpas
    // mas os ponteiros (Demandas) são deletados pelo Simulador.
    demandasAtendidas.clear();
    
    // As listas de objetos (trechos, paradas)
    // limpam seus próprios nós.
    trechos.clear();
    paradas.clear();
}

void Corrida::reconstruirRota() {
    // 1. Limpa listas antigas
    trechos.clear();
    paradas.clear();
    distanciaTotal = 0.0;
    tempoTotal = 0.0;
    numeroParadas = 0;

    int numDemandas = demandasAtendidas.size();
    if (numDemandas == 0) {
        eficiencia = 1.0; // ou 0.0, mas 1.0 faz mais sentido
        return;
    }

    // 2. Cria a lista de Paradas [cite: 44]
    // Ordem: Embarque c0, c1... cn, depois Desembarque c0, c1... cn
    for (int i = 0; i < numDemandas; ++i) {
        Demanda* d = demandasAtendidas.get(i);
        paradas.push_back(Parada(d->origem, EMBARQUE, d));
    }
    for (int i = 0; i < numDemandas; ++i) {
        Demanda* d = demandasAtendidas.get(i);
        paradas.push_back(Parada(d->destino, DESEMBARQUE, d));
    }

    this->numeroParadas = paradas.size();

    // 3. Cria os Trechos ligando as Paradas
    for (int i = 0; i < this->numeroParadas - 1; ++i) {
        Parada* pOrigem = paradas.get(i);
        Parada* pDestino = paradas.get(i + 1);
        
        Trecho novoTrecho(pOrigem, pDestino, this->gama_velocidade);
        trechos.push_back(novoTrecho);
        
        distanciaTotal += novoTrecho.distancia;
        tempoTotal += novoTrecho.tempoGasto;
    }

    // 4. Recalcula a eficiência
    calcularEficiencia();
}

void Corrida::adicionarDemanda(Demanda* demanda) {
    demandasAtendidas.push_back(demanda);
    reconstruirRota();
}

void Corrida::removerUltimaDemanda() {
    demandasAtendidas.pop_back(); // Remove da lista de demandas
    reconstruirRota(); // Reconstrói a rota com as demandas restantes
}

void Corrida::calcularEficiencia() {
    if (demandasAtendidas.empty() || distanciaTotal == 0.0) {
        this->eficiencia = 1.0; // Corrida individual tem 100% [cite: 27]
        return;
    }

    double distanciaIdealSoma = 0.0;
    for (int i = 0; i < demandasAtendidas.size(); ++i) {
        distanciaIdealSoma += demandasAtendidas.get(i)->getDistanciaIdeal();
    }

    // Eficiência = (Soma das distâncias ideais) / (Distância total da rota)
    this->eficiencia = distanciaIdealSoma / this->distanciaTotal;
}