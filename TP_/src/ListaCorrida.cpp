#include "ListaCorrida.h"
#include "Corrida.h" // Definição completa
#include <stdexcept>

// --- Nó ---
NoCorrida::NoCorrida(Corrida* c) : dado(c), proximo(nullptr) {}

// --- Lista ---
ListaCorrida::ListaCorrida() : inicio(nullptr), fim(nullptr), tamanho(0) {}

ListaCorrida::~ListaCorrida() {
    clear();
}

void ListaCorrida::push_back(Corrida* c) {
    NoCorrida* novoNo = new NoCorrida(c);
    if (empty()) {
        inicio = novoNo;
        fim = novoNo;
    } else {
        fim->proximo = novoNo;
        fim = novoNo;
    }
    tamanho++;
}

Corrida* ListaCorrida::get(int index) {
    if (index < 0 || index >= tamanho) {
        throw std::out_of_range("Índice fora dos limites da ListaCorrida");
    }
    NoCorrida* atual = inicio;
    for (int i = 0; i < index; ++i) {
        atual = atual->proximo;
    }
    return atual->dado;
}

int ListaCorrida::size() const { return tamanho; }
bool ListaCorrida::empty() const { return tamanho == 0; }

void ListaCorrida::clear() {
    NoCorrida* atual = inicio;
    while (atual != nullptr) {
        NoCorrida* proximo = atual->proximo;
        delete atual;
        atual = proximo;
    }
    inicio = nullptr;
    fim = nullptr;
    tamanho = 0;
}