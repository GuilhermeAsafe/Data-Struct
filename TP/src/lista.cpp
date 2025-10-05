#include <iostream>
#include <stdexcept> // INCLUA ESTA BIBLIOTECA para usar exceções
#include <algorithm> // Não estritamente necessário para Mergesort manual, mas útil

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


// ... (implementação de listas::insert, listas::print, listas::busca omitidas)

// ----------------------------------------------------
// IMPLEMENTAÇÃO DO MERGESORT PARA LISTA ENCADEADA
// ----------------------------------------------------

/**
 * @brief Encontra o nó do meio da lista usando o método lento/rápido (slow/fast pointers).
 * @param head O nó inicial da lista ou sublista.
 * @return O ponteiro para o nó do meio.
 */
listas::Node* listas::getMiddle(Node* head) {
    if (head == nullptr) {
        return head;
    }

    Node* slow = head;
    Node* fast = head->prox; // Começa um à frente para garantir a primeira metade correta

    while (fast != nullptr) {
        fast = fast->prox;
        if (fast != nullptr) {
            slow = slow->prox;
            fast = fast->prox;
        }
    }
    return slow;
}

/**
 * @brief Combina duas sublistas ordenadas (a e b).
 * @param a Primeira sublista (ordenada).
 * @param b Segunda sublista (ordenada).
 * @return A cabeça da nova lista mesclada e ordenada.
 */
listas::Node* listas::merge(Node* a, Node* b) {
    // Caso base: se uma das listas for nula
    if (a == nullptr) {
        return b;
    }
    if (b == nullptr) {
        return a;
    }

    Node* result = nullptr;

    // A oclusão prioriza o objeto mais próximo (MAIOR Y).
    // Ordenamos em ordem decrescente de Y.
    if (a->obj.y >= b->obj.y) {
        result = a;
        result->prox = merge(a->prox, b);
    } else {
        result = b;
        result->prox = merge(a, b->prox);
    }

    return result;
}

/**
 * @brief Divide a lista e chama a função de merge.
 * @param head O nó inicial da sublista a ser ordenada.
 * @return A cabeça da sublista ordenada.
 */
listas::Node* listas::mergeSort(Node* head) {
    // Caso base: lista nula ou lista com apenas um elemento
    if (head == nullptr || head->prox == nullptr) {
        return head;
    }

    // 1. Encontra o ponto médio
    Node* middle = getMiddle(head);
    Node* nextOfMiddle = middle->prox;

    // 2. Separa a lista em duas metades
    middle->prox = nullptr; // Termina a primeira metade

    // 3. Chama o mergeSort recursivamente para as duas metades
    Node* left = mergeSort(head);
    Node* right = mergeSort(nextOfMiddle);

    // 4. Combina as duas metades ordenadas
    return merge(left, right);
}

/**
 * @brief Função pública que inicia o Mergesort na lista.
 */
void listas::ordenaPorY() {
    // 1. Chama a função recursiva no head
    head = mergeSort(head);
    
    // 2. Atualiza o ponteiro tail (necessário após reordenar a lista)
    Node* current = head;
    while (current != nullptr && current->prox != nullptr) {
        current = current->prox;
    }
    tail = current;
}