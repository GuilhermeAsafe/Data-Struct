#include "include/cena.hpp"
#include "include/lista.hpp"
#include "include/objeto.hpp"
#include <iostream>
#include <algorithm> // Para std::max, std::min (permitidos em C++11 para tipos básicos)
#include <stdexcept>
#include <iomanip> // Adicione esta biblioteca para formatar a saída

// ====================================================================
// FUNÇÕES AUXILIARES INTERNAS
// ====================================================================

// Implementação do Destrutor (limpeza de memória)
Cena::~Cena() {
    Segmento* current = head;
    Segmento* nextNode = nullptr;
    while (current != nullptr) {
        nextNode = current->prox;
        delete current;
        current = nextNode;
    }
    head = nullptr;
    tail = nullptr;
}

// Implementação de inserção de Segmento na lista de resultados da cena
void Cena::insereSegmento(int tempo, float id, float inicio, float fim) {
    if (inicio >= fim) return; // Garante segmento válido

    Segmento* novo = new Segmento(tempo, id, inicio, fim);
    if (head == nullptr) {
        head = novo;
        tail = novo;
    } else {
        tail->prox = novo;
        tail = novo;
    }
}

// Implementação para adicionar (e UNIR) um novo intervalo ocupado.
// Mantém a lista ordenada e com intervalos disjuntos (canônicos).
void Cena::adicionaIntervaloOcupado(IntervaloOcupado** head_ref, float inicio, float fim) {
    if (inicio >= fim) return;

    IntervaloOcupado dummy(0, 0); // Nó sentinela (head falso)
    dummy.prox = *head_ref;
    IntervaloOcupado* prev = &dummy;
    IntervaloOcupado* current = *head_ref;

    // 1. Pula intervalos que estão completamente ANTES do novo
    while (current != nullptr && current->fim < inicio) {
        prev = current;
        current = current->prox;
    }

    // 2. Pula intervalos que estão completamente DEPOIS do novo
    if (current == nullptr || fim < current->inicio) {
        // Insere o novo intervalo sem união
        IntervaloOcupado* novo = new IntervaloOcupado(inicio, fim);
        novo->prox = current;
        prev->prox = novo;
        *head_ref = dummy.prox;
        return;
    }

    // 3. Ocorre sobreposição: atualiza o início e fim para UNIR intervalos
    float novo_inicio = std::min(inicio, current->inicio);
    float novo_fim = fim; 

    // Remove e estende o intervalo atual até que não haja mais sobreposição
    while (current != nullptr && current->inicio <= novo_fim) {
        novo_fim = std::max(novo_fim, current->fim);
        IntervaloOcupado* temp = current;
        current = current->prox;
        delete temp;
    }

    // 4. Insere o novo intervalo UNIDO
    IntervaloOcupado* novo_unido = new IntervaloOcupado(novo_inicio, novo_fim);
    novo_unido->prox = current;
    prev->prox = novo_unido;

    *head_ref = dummy.prox;
}

// ====================================================================
// IMPLEMENTAÇÃO DO MERGESORT PARA SEGMENTO (Ordenação por ID_OBJETO)
// ====================================================================

Cena::Segmento* Cena::getMiddleSegmentos(Segmento* head) {
    if (head == nullptr) {
        return head;
    }

    Segmento* slow = head;
    Segmento* fast = head->prox; 

    while (fast != nullptr) {
        fast = fast->prox;
        if (fast != nullptr) {
            slow = slow->prox;
            fast = fast->prox;
        }
    }
    return slow;
}

Cena::Segmento* Cena::mergeSegmentos(Segmento* a, Segmento* b) {
    if (a == nullptr) return b;
    if (b == nullptr) return a;

    Segmento* result = nullptr;

    // Ordenação ASCENDENTE por id_objeto
    if (a->id_objeto <= b->id_objeto) {
        result = a;
        result->prox = mergeSegmentos(a->prox, b);
    } else {
        result = b;
        result->prox = mergeSegmentos(a, b->prox);
    }

    return result;
}

Cena::Segmento* Cena::mergeSortSegmentos(Segmento* head) {
    if (head == nullptr || head->prox == nullptr) {
        return head;
    }

    Segmento* middle = getMiddleSegmentos(head);
    Segmento* nextOfMiddle = middle->prox;

    middle->prox = nullptr; 

    Segmento* left = mergeSortSegmentos(head);
    Segmento* right = mergeSortSegmentos(nextOfMiddle);

    return mergeSegmentos(left, right);
}


// ====================================================================
// FUNÇÃO DE SAÍDA CORRIGIDA (Chama a ordenação antes de imprimir)
// ====================================================================

 // ... (código anterior omitido)

void Cena::gravaCena() {
    // 1. ORDENAR A LISTA DE SEGMENTOS POR id_objeto (ASCENDENTE)
    head = mergeSortSegmentos(head);
    
    // 2. Configurar a precisão para todas as saídas decimais
    std::cout << std::fixed << std::setprecision(2); // PADRÃO DE DUAS CASAS DECIMAIS
    
    // 3. Imprimir a lista ordenada e limpar a memória
    Segmento* current = head;
    
    while (current != nullptr) {
        // Formato de saída: S <tempo> <objeto> <inicio> <fim>
        std::cout << "S " 
                  << current->tempo << " " 
                  << (int)current->id_objeto 
                  << " " << current->inicio  // A precisão de 2 casas é aplicada aqui
                  << " " << current->fim     // E aqui
                  << std::endl
                  << std::endl;
        
        // Limpeza do segmento após a impressão
        Segmento* a_remover = current;
        current = current->prox;
        delete a_remover;
    }

    // Opcional: Reverter a formatação padrão do stream, para o caso de uso posterior.
    std::cout << std::defaultfloat; 

    // Resetar head e tail após a limpeza
    head = nullptr;
    tail = nullptr;
}


// ====================================================================
// MÉTODO PRINCIPAL: processaCena
// ====================================================================

void Cena::processaCena(listas& lista_objetos, float tempo_cena) {
    // A lista DEVE estar ordenada por Y (distância ao observador) -
    // O objeto mais próximo (menor Y) deve ser o primeiro.
    // Assumimos que lista_objetos.ordenaPorY() foi chamada ANTES (em main.cpp).

    // Estrutura para rastrear a oclusão (o 'canvas' 1D)
    IntervaloOcupado* canvas_ocupado = nullptr;
    
    // Obter o cabeçalho da lista de objetos
    listas::Node* current_obj = lista_objetos.getHead(); 

    while (current_obj != nullptr) {
        objetos& obj = current_obj->obj;

        // 1. Calcular o intervalo do objeto
        float obj_min_x = obj.x - obj.largura / 2.0;
        float obj_max_x = obj.x + obj.largura / 2.0;

        // 2. Fragmentar o objeto com base nos intervalos já ocupados (oclusão)
        float ponto_de_inicio = obj_min_x;
        IntervaloOcupado* ocupado = canvas_ocupado;

        // Percorre os blocos oclusos no 'canvas'
        while (ocupado != nullptr && ponto_de_inicio < obj_max_x) {
            
            // 2a. Existe um segmento visível ANTES do bloco ocupado?
            if (ponto_de_inicio < ocupado->inicio) {
                // O segmento visível é [ponto_de_inicio, min(obj_max_x, ocupado->inicio)]
                float fim_visivel = std::min(obj_max_x, ocupado->inicio);
                
                if (fim_visivel > ponto_de_inicio) {
                    // Adiciona a parte visível aos resultados da cena
                    insereSegmento((int)tempo_cena, obj.id_objeto, ponto_de_inicio, fim_visivel);
                }
            }
            
            // 2b. O próximo ponto de início para busca é o fim do bloco ocupado.
            // (Se o objeto for maior que o bloco, avança; se for menor, oclui totalmente essa parte)
            if (ocupado->fim > ponto_de_inicio) {
                ponto_de_inicio = ocupado->fim;
            }

            ocupado = ocupado->prox;
        }

        // 3. Existe um segmento visível APÓS o último bloco ocupado?
        if (ponto_de_inicio < obj_max_x) {
            // O segmento visível é [ponto_de_inicio, obj_max_x]
            insereSegmento((int)tempo_cena, obj.id_objeto, ponto_de_inicio, obj_max_x);
        }

        // 4. Adicionar o intervalo TOTAL do objeto (mesmo o ocluso) ao canvas para bloquear
        // objetos que estão ainda mais atrás.
        adicionaIntervaloOcupado(&canvas_ocupado, obj_min_x, obj_max_x);
        
        current_obj = current_obj->prox;
    }
    
    // Limpar a memória temporária do canvas
    IntervaloOcupado* current_canvas = canvas_ocupado;
    IntervaloOcupado* next_canvas = nullptr;
    while (current_canvas != nullptr) {
        next_canvas = current_canvas->prox;
        delete current_canvas;
        current_canvas = next_canvas;
    }
    
    // Gravação da cena (chamada no main.cpp)
}




