#include <iostream>
#include <stdexcept> 
#include <algorithm> 

#include "include/lista.hpp"
#include "include/objeto.hpp"
#include "include/movimento.hpp"

// ==========================================================
// FUNÇÕES DE MANIPULAÇÃO DA LISTA (CRUD)
// ==========================================================

/**
 * @brief Insere um novo objeto no final da lista encadeada.
 * @param obj Objeto a ser inserido.
 */
void listas::insert(objetos obj)
{
    Node* newNode = new Node(obj); // Cria novo nó (alocação de memória)

    if (head == nullptr) // Lista vazia
    {
        head = newNode;
        tail = newNode;
    }
    else // Lista não vazia
    {
        tail->prox = newNode; 
        tail = newNode;       // Atualiza o ponteiro tail
    }
}

/**
 * @brief Imprime todos os objetos da lista (uso de debug).
 */
void listas::print()
{
    Node* current = head;
    while (current)
    {
        std::cout << "ID: " << current->obj.id << ", Centro: " << current->obj.id_objeto
                  << ", X: " << current->obj.x << ", Y: " << current->obj.y
                  << ", Largura: " << current->obj.largura << std::endl;
        current = current->prox;
    }
}

/**
 * @brief Busca um objeto pelo seu ID e retorna a referência para ele.
 * @param chave_objeto ID do objeto a ser buscado.
 * @return Referência para o objeto encontrado na lista.
 * @throws std::runtime_error se o objeto não for encontrado.
 */
objetos& listas::busca(double chave_objeto)
{
    Node* current = head;
    while (current)
    {
        if (current->obj.id_objeto == chave_objeto)
        {
            return current->obj; 
        }
        current = current->prox;
    }
     
    throw std::runtime_error("Erro: Objeto não encontrado na lista com a chave especificada.");
}

// ==========================================================
// DESTRUTOR (Limpeza de Memória)
// ==========================================================

/**
 * @brief Destrutor da lista. Libera a memória de todos os nós.
 */
listas::~listas() {
    Node* current = head;
    Node* nextNode = nullptr;
    while (current != nullptr)
    {
        nextNode = current->prox;
        delete current; // Libera a memória do nó
        current = nextNode;
    }
    head = nullptr;
    tail = nullptr;
}

// ==========================================================
// IMPLEMENTAÇÃO DO MERGESORT (Ordenação por Y)
// ==========================================================

/**
 * @brief Encontra o nó do meio da lista (slow/fast pointers).
 */
listas::Node* listas::getMiddle(Node* head) {
    if (head == nullptr) {
        return head;
    }

    Node* slow = head;
    Node* fast = head->prox; 

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
 * @brief Combina duas sublistas ordenadas.
 * A ordenação é feita de forma DECEDENTE de Y (para oclusão: objetos mais longe primeiro).
 */
listas::Node* listas::merge(Node* a, Node* b) {
    if (a == nullptr) return b;
    if (b == nullptr) return a;

    Node* result = nullptr;

    // Lógica de ordenação: a.obj.y <= b.obj.y garante que o objeto mais longe (menor Y) vá primeiro
    if (a->obj.y <= b->obj.y) {
        result = a;
        result->prox = merge(a->prox, b);
    } else {
        result = b;
        result->prox = merge(a, b->prox);
    }

    return result;
}

/**
 * @brief Divide a lista e chama a função de merge (recursivamente).
 */
listas::Node* listas::mergeSort(Node* head) {
    if (head == nullptr || head->prox == nullptr) {
        return head;
    }

    // 1. Encontra o ponto médio
    Node* middle = getMiddle(head);
    Node* nextOfMiddle = middle->prox;

    // 2. Separa a lista em duas metades
    middle->prox = nullptr; 

    // 3. Chama o mergeSort recursivamente
    Node* left = mergeSort(head);
    Node* right = mergeSort(nextOfMiddle);

    // 4. Combina as duas metades ordenadas
    return merge(left, right);
}

/**
 * @brief Inicia o Mergesort na lista principal.
 */
void listas::ordenaPorY() {
    // 1. Chama a função recursiva no head
    head = mergeSort(head);
    
    // 2. Atualiza o ponteiro tail
    Node* current = head;
    while (current != nullptr && current->prox != nullptr) {
        current = current->prox;
    }
    tail = current;
}