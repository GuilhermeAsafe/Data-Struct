#include "ListaDemanda.h"
#include <stdexcept>

// --- Implementação do Nó ---
NoDemanda::NoDemanda(Demanda* d) 
    : dado(d), proximo(nullptr) 
{}

// --- Implementação da Lista ---
ListaDemanda::ListaDemanda() 
    : inicio(nullptr), fim(nullptr), tamanho(0) 
{}

ListaDemanda::~ListaDemanda() {
    clear();
}

void ListaDemanda::push_back(Demanda* d) {
    NoDemanda* novoNo = new NoDemanda(d);
    if (empty()) {
        inicio = novoNo;
        fim = novoNo;
    } else {
        fim->proximo = novoNo;
        fim = novoNo;
    }
    tamanho++;
}

Demanda* ListaDemanda::get(int index) {
    if (index < 0 || index >= tamanho) {
        throw std::out_of_range("Índice fora dos limites da ListaDemanda");
    }

    NoDemanda* atual = inicio;
    for (int i = 0; i < index; ++i) {
        atual = atual->proximo;
    }
    return atual->dado;
}

int ListaDemanda::size() const {
    return tamanho;
}

bool ListaDemanda::empty() const {
    return tamanho == 0;
}

void ListaDemanda::clear() {
    NoDemanda* atual = inicio;
    while (atual != nullptr) {
        NoDemanda* proximo = atual->proximo;
        delete atual; // Deleta o nó
        // NÃO deletamos atual->dado (a Demanda)
        atual = proximo;
    }
    inicio = nullptr;
    fim = nullptr;
    tamanho = 0;
}