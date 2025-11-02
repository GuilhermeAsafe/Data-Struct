#include "ListaDemanda.h"
#include <stdexcept>

// --- Nó ---
NoDemanda::NoDemanda(Demanda* d) : dado(d), proximo(nullptr) {}

// --- Lista ---
ListaDemanda::ListaDemanda() : inicio(nullptr), fim(nullptr), tamanho(0) {}

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

Demanda* ListaDemanda::pop_back() {
    if (empty()) {
        throw std::out_of_range("pop_back() em ListaDemanda vazia");
    }
    
    Demanda* dadoRemovido = fim->dado;
    
    if (tamanho == 1) {
        delete inicio;
        inicio = nullptr;
        fim = nullptr;
    } else {
        NoDemanda* atual = inicio;
        while (atual->proximo != fim) {
            atual = atual->proximo;
        }
        delete fim;
        fim = atual;
        fim->proximo = nullptr;
    }
    
    tamanho--;
    return dadoRemovido;
}

int ListaDemanda::size() const { return tamanho; }
bool ListaDemanda::empty() const { return tamanho == 0; }

void ListaDemanda::clear() {
    NoDemanda* atual = inicio;
    while (atual != nullptr) {
        NoDemanda* proximo = atual->proximo;
        delete atual; // Deleta o nó
        atual = proximo;
    }
    inicio = nullptr;
    fim = nullptr;
    tamanho = 0;
}