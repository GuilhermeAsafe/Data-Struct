#include <iostream>
#include <stdexcept> // INCLUA ESTA BIBLIOTECA para usar exceções

#include "include/lista.hpp"
#include "include/objeto.hpp"
#include "include/movimento.hpp"

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

objetos& listas::busca(float chave_objeto)
{
    Node* current = head;
    while (current)
    {
        // A chave de busca (objeto) é o campo 'centro_objeto'
        if (current->obj.centro_objeto == chave_objeto)
        {
            // Retorna a referência do objeto real no nó
            return current->obj; 
        }
        current = current->prox;
    }
     
    // Se o loop terminar sem encontrar, lança uma exceção.
    // É OBRIGATÓRIO que uma função que retorna uma referência retorne algo.
    throw std::runtime_error("Erro: Objeto não encontrado na lista com a chave especificada.");
}
