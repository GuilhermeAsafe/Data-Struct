#ifndef ESCALONADOR_H
#define ESCALONADOR_H

#include "MinHeap.h"
#include "Evento.h"

class Escalonador {
private:
    MinHeap heap; // O escalonador "CONTÉM" um MinHeap

public:
    /**
     * Operação 1: Inicializa (o construtor faz isso)
     */
    Escalonador();

    /**
     * Operação 4: Finaliza (o destrutor faz isso)
     */
    ~Escalonador();

    /**
     * Operação 2: Insere Evento [cite: 1064]
     */
    void InsereEvento(Evento* evento);

    /**
     * Operação 3: Retira Proximo Evento [cite: 1065]
     */
    Evento* RetiraProximoEvento();

    /**
     * Função auxiliar para o loop da simulação.
     */
    bool estaVazio() const;
};

#endif // ESCALONADOR_H