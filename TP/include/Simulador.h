#ifndef SIMULADOR_H
#define SIMULADOR_H

#include "Estruturas.h" 
#include <iostream> // Necessário para std::istream

class Simulador {
private:
    // Parâmetros da simulação
    int eta; // Capacidade
    double gama, delta, alfa, beta, lambda;

    MinHeap heap; 
    ListaDemanda listaDeTodasDemandas;
    ListaCorrida listaDeTodasCorridas; 
    bool* demandasProcessadas; 
    int numTotalDemandas;

public:
    Simulador();
    ~Simulador(); 

    /**
     * Carrega os dados de um stream de entrada (cin ou fstream).
     * --- MODIFICADO ---
     */
    void carregarEntrada(std::istream& input); 

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
     * (Versão VPL - 1 argumento)
     */
    void processarEvento(Evento* evento); 
};

#endif // SIMULADOR_H