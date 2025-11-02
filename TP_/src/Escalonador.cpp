#include "Escalonador.h"

Escalonador::Escalonador() {
    // 1. Inicializa: O construtor do MinHeap já é chamado aqui,
    // inicializando a fila de prioridade.
}

Escalonador::~Escalonador() {
    // 4. Finaliza: O destrutor do MinHeap será chamado aqui,
    // limpando toda a memória alocada para os Eventos.
    // Estatísticas de escalonamento (se necessário) seriam geradas aqui[cite: 1068].
}

void Escalonador::InsereEvento(Evento* evento) {
    // 2. Insere Evento: Apenas repassa para o MinHeap.
    heap.inserir(evento);
}

Evento* Escalonador::RetiraProximoEvento() {
    // 3. Retira Proximo Evento: Apenas repassa do MinHeap.
    return heap.removerMin();
}

bool Escalonador::estaVazio() const {
    return heap.estaVazio();
}