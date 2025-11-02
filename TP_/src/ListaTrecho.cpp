#include "ListaTrecho.h"
#include <stdexcept>

// --- Implementação do Nó ---
NoTrecho::NoTrecho(Trecho t) 
    : dado(t), proximo(nullptr) 
{}

// --- Implementação da Lista ---
ListaTrecho::ListaTrecho() 
    : inicio(nullptr), fim(nullptr), tamanho(0) 
{}

ListaTrecho::~ListaTrecho() {
    clear();
}

void ListaTrecho::push_back(Trecho t) {
    NoTrecho* novoNo = new NoTrecho(t);
    if (empty()) {
        inicio = novoNo;
        fim = novoNo;
    } else {
        fim->proximo = novoNo;
        fim = novoNo;
    }
    tamanho++;
}

Trecho& ListaTrecho::get(int index) {
    if (index < 0 || index >= tamanho) {
        throw std::out_of_range("Índice fora dos limites da ListaTrecho");
    }

    NoTrecho* atual = inicio;
    for (int i = 0; i < index; ++i) {
        atual = atual->proximo;
    }
    return atual->dado;
}

int ListaTrecho::size() const {
    return tamanho;
}

bool ListaTrecho::empty() const {
    return tamanho == 0;
}

void ListaTrecho::clear() {
    NoTrecho* atual = inicio;
    while (atual != nullptr) {
        NoTrecho* proximo = atual->proximo;
        delete atual; // Deleta o nó
        atual = proximo;
    }
    inicio = nullptr;
    fim = nullptr;
    tamanho = 0;
}