#include "MinHeap.h"
#include <stdexcept>

MinHeap::MinHeap() : capacidade(10), tamanho(0) {
    dados = new Evento*[capacidade];
}

MinHeap::~MinHeap() {
    for (int i = 0; i < tamanho; ++i) {
        delete dados[i];
    }
    delete[] dados;
}

void MinHeap::redimensionar() {
    capacidade *= 2;
    Evento** novosDados = new Evento*[capacidade];
    for (int i = 0; i < tamanho; ++i) {
        novosDados[i] = dados[i];
    }
    delete[] dados;
    dados = novosDados;
}

void MinHeap::swap(int i, int j) {
    Evento* temp = dados[i];
    dados[i] = dados[j];
    dados[j] = temp;
}

void MinHeap::heapifyUp(int index) {
    // Compara o evento no índice com seu pai
    // *dados[index] > *dados[getParent(index)] usa o operador > de Evento.h
    
    // CORREÇÃO: Adiciona parênteses em volta da comparação
    while (index > 0 && (*dados[index] > *dados[getParent(index)] == false)) {
        swap(index, getParent(index));
        index = getParent(index);
    }
}

void MinHeap::heapifyDown(int index) {
    int left = getLeftChild(index);
    int right = getRightChild(index);
    int menor = index;

    // CORREÇÃO: Adiciona parênteses em volta da comparação
    if (left < tamanho && (*dados[left] > *dados[menor] == false)) {
        menor = left;
    }
    if (right < tamanho && (*dados[right] > *dados[menor] == false)) {
        menor = right;
    }

    if (menor != index) {
        swap(index, menor);
        heapifyDown(menor);
    }
}

void MinHeap::inserir(Evento* evento) {
    if (tamanho == capacidade) {
        redimensionar();
    }
    dados[tamanho] = evento;
    tamanho++;
    heapifyUp(tamanho - 1);
}

Evento* MinHeap::removerMin() {
    if (estaVazio()) {
        return nullptr;
    }
    Evento* minEvento = dados[0];
    dados[0] = dados[tamanho - 1];
    tamanho--;
    
    if (tamanho > 0) {
        heapifyDown(0);
    }
    
    return minEvento;
}

bool MinHeap::estaVazio() const {
    return tamanho == 0;
}