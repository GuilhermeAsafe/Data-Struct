#include "Escalonador.h"

Escalonador::Escalonador() {
    // 1. Inicializa: Construtor do MinHeap é chamado
}

Escalonador::~Escalonador() {
    // 4. Finaliza: Destrutor do MinHeap é chamado
}

void Escalonador::InsereEvento(Evento* evento) {
    // 2. Insere Evento
    heap.inserir(evento);
}

Evento* Escalonador::RetiraProximoEvento() {
    // 3. Retira Proximo Evento
    return heap.removerMin();
}

bool Escalonador::estaVazio() const {
    return heap.estaVazio();
}