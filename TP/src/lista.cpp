#include <iostream>

#include "include/lista.hpp"


void listas::insert(objetos obj)
{
    Node* newNode = new Node(obj); // cria novo nó
    //newNode->prox = nullptr;

    if (head == nullptr) // lista vazia
    {
        head = newNode;
        tail = newNode;
    }
    else // lista não vazia
    {
        tail->prox = newNode; // liga o último nó ao novo
        tail = newNode;       // atualiza o tail
    }
}


void listas::print()
{
    Node* current = head;
    while (current)
    {
        std::cout << "ID: " << current->obj.id << ", Centro: " << current->obj.centro_objeto
                  << ", X: " << current->obj.x << ", Y: " << current->obj.y
                  << ", Largura: " << current->obj.largura << std::endl;
        current = current->prox;
    }
}