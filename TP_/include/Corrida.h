#ifndef CORRIDA_H
#define CORRIDA_H

// #include "Lista.h" // REMOVIDO
#include "ListaDemanda.h" // ADICIONADO
#include "ListaTrecho.h"  // ADICIONADO

#include "Trecho.h"
#include "Demanda.h"

class Corrida {
public:
    // MODIFICADO: Usa as listas encadeadas específicas
    ListaDemanda demandasAtendidas;
    ListaTrecho trechos;

    double distanciaTotal;
    double tempoTotal;
    double eficiencia;
    int numeroParadas;

    Corrida();

    /**
     * Adiciona uma demanda a esta corrida.
     * (Você precisará de lógica para reconstruir os trechos)
     */
    void adicionarDemanda(Demanda* demanda, double gama);
    
    /**
     * Adiciona um trecho à corrida e atualiza estatísticas.
     */
    void adicionarTrecho(Trecho trecho);

    /**
     * Calcula a eficiência da corrida [cite: 904-906].
     * (Você precisará implementar esta lógica complexa)
     */
    void calcularEficiencia();
};

#endif // CORRIDA_H