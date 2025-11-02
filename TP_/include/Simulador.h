#ifndef SIMULADOR_H
#define SIMULADOR_H

#include "Escalonador.h"
#include "ListaDemanda.h" // A lista de demandas lidas

class Simulador {
private:
    // Parâmetros da simulação [cite: 1004-1009]
    double eta, gama, delta, alfa, beta, lambda;

    // Estruturas centrais
    Escalonador escalonador;
    ListaDemanda listaDeTodasDemandas;
    // Você também precisará de uma lista para as Corridas geradas

public:
    Simulador();

    /**
     * Carrega o arquivo de entrada, lendo os parâmetros e
     * preenchendo a 'listaDeTodasDemandas'.
     */
    void carregarEntrada(const char* nomeArquivo);

    /**
     * Fase 1: Processa a 'listaDeTodasDemandas' para criar as
     * Corridas e agendar o primeiro evento de cada uma
     * no escalonador[cite: 915].
     */
    void processarDemandas();

    /**
     * Fase 2: Executa o loop principal da simulação,
     * retirando eventos do escalonador até que ele
     * esteja vazio[cite: 927].
     */
    void executar();

private:
    /**
     * Função auxiliar para processar um único evento
     * retirado do escalonador.
     */
    void processarEvento(Evento* evento);
};

#endif // SIMULADOR_H