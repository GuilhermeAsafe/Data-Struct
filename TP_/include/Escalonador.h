#ifndef ESCALONADOR_H
#define ESCALONADOR_H

#include "MinHeap.h"
#include "Evento.h"

class Escalonador {
private:
    MinHeap heap;

public:
    Escalonador();  // 1. Inicializa
    ~Escalonador(); // 4. Finaliza

    void InsereEvento(Evento* evento);       // 2. Insere Evento
    Evento* RetiraProximoEvento(); // 3. Retira Proximo Evento
    bool estaVazio() const;
};

#endif // ESCALONADOR_H