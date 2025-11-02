#ifndef CORRIDA_H
#define CORRIDA_H

#include "ListaDemanda.h"
#include "ListaTrecho.h"
#include "ListaParada.h" // A Corrida "possui" as Paradas
#include "Trecho.h"
#include "Demanda.h"

class Corrida {
private:
    double gama_velocidade; // Salva a velocidade do veículo

    /**
     * Reconstrói as listas 'paradas' e 'trechos' com base
     * na lista 'demandasAtendidas'.
     * Esta é a lógica da "versão básica".
     */
    void reconstruirRota();

public:
    ListaDemanda demandasAtendidas;
    ListaTrecho trechos;
    ListaParada paradas; // Armazena as paradas reais

    double distanciaTotal;
    double tempoTotal;
    double eficiencia;
    int numeroParadas;

    Corrida(double gama); // Construtor precisa da velocidade
    ~Corrida(); // Destrutor para limpar as listas

    /**
     * Adiciona uma demanda a esta corrida e reconstrói a rota.
     */
    void adicionarDemanda(Demanda* demanda);

    /**
     * Remove a última demanda adicionada e reconstrói a rota.
     */
    void removerUltimaDemanda();
    
    /**
     * Calcula a eficiência da corrida.
     */
    void calcularEficiencia();
};

#endif // CORRIDA_H