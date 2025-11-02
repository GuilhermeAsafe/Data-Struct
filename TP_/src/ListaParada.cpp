#include "ListaParada.h"
#include <stdexcept>

// --- Nó ---
NoParada::NoParada(Parada p) : dado(p), proximo(nullptr) {}

// --- Lista ---
ListaParada::ListaParada() : inicio(nullptr), fim(nullptr), tamanho(0) {}

ListaParada::~ListaParada() {
    clear();
}

void ListaParada::push_back(Parada p) {
    NoParada* novoNo = new NoParada(p);
    if (empty()) {
        inicio = novoNo;
        fim = novoNo;
    } else {
        fim->proximo = novoNo;
        fim = novoNo;
    }
    tamanho++;
}

Parada* ListaParada::get(int index) {
    if (index < 0 || index >= tamanho) {
        throw std::out_of_range("Índice fora dos limites da ListaParada");
    }
    NoParada* atual = inicio;
    for (int i = 0; i < index; ++i) {
        atual = atual->proximo;
    }
    return &(atual->dado); // Retorna ponteiro para o dado
}

int ListaParada::size() const { return tamanho; }
bool ListaParada::empty() const { return tamanho == 0; }

void ListaParada::clear() {
    NoParada* atual = inicio;
    while (atual != nullptr) {
        NoParada* proximo = atual->proximo;
        delete atual;
        atual = proximo;
    }
    inicio = nullptr;
    fim = nullptr;
    tamanho = 0;
}