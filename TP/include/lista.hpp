#ifndef LISTA_HPP
#define LISTA_HPP

#include "include/objeto.hpp"

class listas
{

private:

    struct Node
    {
        objetos obj;

        Node* prox;

        Node(objetos obj) : obj(obj), prox(nullptr) {}

    };

    Node* head = nullptr;
    Node* tail =  nullptr;

public:

 

// Em lista.cpp
     // ~listas(); // Declaração do destrutor


    void insert(objetos obj);
    void print();
    objetos& busca(float obj_busca); 
    // void lista::remove(float objeto);
    // void lista::procurar(float objeto);


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
 