#ifndef MINHEAP_H
#define MINHEAP_H

#include "Evento.h"

class MinHeap {
private:
    Evento** dados;
    int capacidade;
    int tamanho;

    void redimensionar();
    void heapifyUp(int index);
    void heapifyDown(int index);
    void swap(int i, int j);

    int getParent(int i) { return (i - 1) / 2; }
    int getLeftChild(int i) { return 2 * i + 1; }
    int getRightChild(int i) { return 2 * i + 2; }

public:
    MinHeap();
    ~MinHeap();

    void inserir(Evento* evento);
    Evento* removerMin();
    bool estaVazio() const;
};

#endif // MINHEAP_H