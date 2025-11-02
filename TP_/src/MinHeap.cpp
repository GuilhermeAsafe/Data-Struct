#include "MinHeap.h"
#include <stdexcept> // Para std::out_of_range

MinHeap::MinHeap() : capacidade(10), tamanho(0) {
    dados = new Evento*[capacidade];
}

MinHeap::~MinHeap() {
    // Deleta todos os Eventos restantes no heap
    for (int i = 0; i < tamanho; ++i) {
        delete dados[i];
    }
    // Deleta o array de ponteiros
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
    // *dados[index] > *dados[getParent(index)] usa o operador > que definimos em Evento.h
    while (index > 0 && *dados[index] > *dados[getParent(index)] == false) {
        swap(index, getParent(index));
        index = getParent(index);
    }
}

void MinHeap::heapifyDown(int index) {
    int left = getLeftChild(index);
    int right = getRightChild(index);
    int menor = index;

    // Encontra o menor entre o nó atual e seus filhos
    if (left < tamanho && *dados[left] > *dados[menor] == false) {
        menor = left;
    }
    if (right < tamanho && *dados[right] > *dados[menor] == false) {
        menor = right;
    }

    // Se o menor não for o nó atual, troca e continua descendo
    if (menor != index) {
        swap(index, menor);
        heapifyDown(menor);
    }
}

void MinHeap::inserir(Evento* evento) {
    if (tamanho == capacidade) {
        redimensionar();
    }
    // Adiciona no final
    dados[tamanho] = evento;
    tamanho++;
    // Sobe para a posição correta
    heapifyUp(tamanho - 1);
}

Evento* MinHeap::removerMin() {
    if (estaVazio()) {
        return nullptr;
    }
    // O menor está na raiz
    Evento* minEvento = dados[0];
    
    // Move o último elemento para a raiz
    dados[0] = dados[tamanho - 1];
    tamanho--;
    
    // Desce com o novo elemento da raiz para manter a propriedade
    if (tamanho > 0) {
        heapifyDown(0);
    }
    
    return minEvento; // Retorna o evento original da raiz
}

Evento* MinHeap::getProximo() const {
    if (estaVazio()) {
        return nullptr;
    }
    return dados[0];
}

bool MinHeap::estaVazio() const {
    return tamanho == 0;
}

int MinHeap::getSize() const {
    return tamanho;
}