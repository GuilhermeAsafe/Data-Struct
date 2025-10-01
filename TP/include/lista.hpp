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

    void insert(objetos obj);
    void print();
    void busca(float obj_busca);
    // void lista::remove(float objeto);
    // void lista::procurar(float objeto);
    
};

#endif
 