#ifndef MINHEAP_H
#define MINHEAP_H

#include "Evento.h"

class MinHeap {
private:
    Evento** dados;   // Array dinâmico de PONTEIROS para Eventos
    int capacidade;
    int tamanho;

    /**
     * Dobra a capacidade do array interno.
     */
    void redimensionar();

    /**
     * Move um elemento para cima no heap para manter a propriedade.
     */
    void heapifyUp(int index);

    /**
     * Move um elemento para baixo no heap para manter a propriedade.
     */
    void heapifyDown(int index);

    /**
     * Troca dois elementos no array.
     */
    void swap(int i, int j);

    // Funções auxiliares de índice
    int getParent(int i) { return (i - 1) / 2; }
    int getLeftChild(int i) { return 2 * i + 1; }
    int getRightChild(int i) { return 2 * i + 2; }

public:
    /**
     * Construtor: Inicia o heap.
     */
    MinHeap();

    /**
     * Destrutor: Libera toda a memória (deleta os Eventos e o array).
     */
    ~MinHeap();

    /**
     * Insere um novo evento no heap.
     */
    void inserir(Evento* evento);

    /**
     * Remove e retorna o evento com o menor tempo (a raiz).
     * Retorna nullptr se o heap estiver vazio.
     */
    Evento* removerMin();

    /**
     * Retorna o próximo evento (a raiz) sem removê-lo.
     * Retorna nullptr se o heap estiver vazio.
     */
    Evento* getProximo() const;

    /**
     * Verifica se o heap está vazio.
     */
    bool estaVazio() const;

    /**
     * Retorna o número de eventos no heap.
     */
    int getSize() const;
};

#endif // MINHEAP_H