#ifndef SIMULADOR_H
#define SIMULADOR_H

#include "Escalonador.h"
#include "ListaDemanda.h"
#include "ListaCorrida.h" // Para guardar as corridas criadas

class Simulador {
private:
    // Parâmetros da simulação
    int eta; // Capacidade
    double gama, delta, alfa, beta, lambda;

    Escalonador escalonador;
    ListaDemanda listaDeTodasDemandas;
    ListaCorrida listaDeTodasCorridas; // Para gerenciar memória
    bool* demandasProcessadas; // Array para marcar demandas já alocadas
    int numTotalDemandas;

public:
    Simulador();
    ~Simulador(); // Destrutor para limpar a memória alocada

    /**
     * Carrega o arquivo de entrada.
     */
    void carregarEntrada(const char* nomeArquivo);

    /**
     * Fase 1: Processa 'listaDeTodasDemandas' para criar Corridas
     * e agendar o primeiro evento de cada uma.
     */
    void processarDemandas();

    /**
     * Fase 2: Executa o loop principal da simulação.
     */
    void executar();

private:
    /**
     * Função auxiliar para processar um único evento.
     */
    void processarEvento(Evento* evento);
};

#endif // SIMULADOR_H