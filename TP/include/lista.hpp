#ifndef LISTA_HPP
#define LISTA_HPP

#include "include/objeto.hpp"

class listas
{

public:

    struct Node
    {
        objetos obj;

        Node* prox;

        Node(objetos obj) : obj(obj), prox(nullptr) {}

    };

    Node* head = nullptr;
    Node* tail =  nullptr;

    // Métodos auxiliares privados para o Mergesort
    Node* mergeSort(Node* head); 
    Node* merge(Node* a, Node* b);
    Node* getMiddle(Node* head);

    Node* getHead() const { return head; } // <--- Adicione esta linha

public:

 

// Em lista.cpp
     // ~listas(); // Declaração do destrutor


    void insert(objetos obj);
    void print();
    objetos& busca(double obj_busca); 

     void ordenaPorY();


    // void lista::remove(double objeto);
    // void lista::procurar(double objeto);


//     ~listas(){
//     Node* current = head;
//     Node* nextNode = nullptr;
//     while (current != nullptr)
//     {
//         nextNode = current->prox;
//         delete current;
//         current = nextNode;
//     }
// }
    
};

#endif
 