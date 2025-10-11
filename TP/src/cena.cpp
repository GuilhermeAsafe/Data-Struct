#include "include/cena.hpp"
#include "include/lista.hpp"
#include "include/objeto.hpp"
#include <iostream>
#include <algorithm> // Para std::max, std::min
#include <stdexcept>
#include <iomanip> 

// ====================================================================
// DESTRUTOR E FUNÇÕES DE INSERÇÃO
// ====================================================================

/**
 * @brief Destrutor: Libera a memória da lista de Segmentos.
 * (Nota: Em main.cpp, os Segmentos são deletados e o head/tail zerados antes
 * que este destrutor seja chamado para evitar double free).
 */
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

/**
 * @brief Insere um novo Segmento visível na lista de resultados da cena.
 */
void Cena::insereSegmento(int tempo, double id, double inicio, double fim) {
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

/**
 * @brief Adiciona/Une um novo intervalo ocupado ao 'canvas'.
 * Mantém a lista de Intervalos Ocupados ordenada e canônica (disjunta).
 */
void Cena::adicionaIntervaloOcupado(IntervaloOcupado** head_ref, double inicio, double fim) {
    if (inicio >= fim) return;

    IntervaloOcupado dummy(0, 0); 
    dummy.prox = *head_ref;
    IntervaloOcupado* prev = &dummy;
    IntervaloOcupado* current = *head_ref;

    // 1. Pula intervalos existentes que estão ANTES do novo
    while (current != nullptr && current->fim < inicio) {
        prev = current;
        current = current->prox;
    }

    // 2. Se não houver sobreposição, insere o novo intervalo
    if (current == nullptr || fim < current->inicio) {
        IntervaloOcupado* novo = new IntervaloOcupado(inicio, fim);
        novo->prox = current;
        prev->prox = novo;
        *head_ref = dummy.prox;
        return;
    }

    // 3. Ocorre sobreposição: inicia a união
    double novo_inicio = std::min(inicio, current->inicio);
    double novo_fim = fim; 

    // Remove e estende o intervalo atual até que a sobreposição termine
    while (current != nullptr && current->inicio <= novo_fim) {
        novo_fim = std::max(novo_fim, current->fim);
        IntervaloOcupado* temp = current;
        current = current->prox;
        delete temp; // Libera memória do intervalo que está sendo unido
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

/**
 * @brief Encontra o nó do meio da lista de Segmentos.
 */
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

/**
 * @brief Combina duas sublistas ordenadas de Segmentos.
 */
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

/**
 * @brief Divide a lista e chama a função de merge para Segmentos.
 */
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
// FUNÇÃO DE SAÍDA (Apenas Ordena)
// ====================================================================

/**
 * @brief Ordena a lista interna de Segmentos por id_objeto.
 * (A transferência de dados e limpeza de memória é feita em main.cpp).
 */
void Cena::gravaCena() {
    // Ordena a lista de Segmentos por id_objeto (ASCENDENTE)
    head = mergeSortSegmentos(head);
}


// ====================================================================
// MÉTODO PRINCIPAL: processaCena
// ====================================================================

/**
 * @brief Processa a oclusão para todos os objetos na lista e gera os Segmentos visíveis.
 * @param lista_objetos Lista de objetos ordenada por Y (distância).
 * @param tempo_cena O tempo atual da cena.
 */
void Cena::processaCena(listas& lista_objetos, double tempo_cena) {
    
    // Lista para rastrear os intervalos de X que já estão bloqueados por objetos mais próximos
    IntervaloOcupado* canvas_ocupado = nullptr;
    
    listas::Node* current_obj = lista_objetos.getHead(); 

    // Itera sobre os objetos, do mais próximo para o mais distante (graças à ordenação por Y)
    while (current_obj != nullptr) {
        objetos& obj = current_obj->obj;

        // 1. Calcular o intervalo total de X do objeto
        double obj_min_x = obj.x - obj.largura / 2.0;
        double obj_max_x = obj.x + obj.largura / 2.0;

        // 2. Fragmentar o objeto com base nos intervalos já ocupados (oclusão)
        double ponto_de_inicio = obj_min_x;
        IntervaloOcupado* ocupado = canvas_ocupado;

        // Percorre os blocos oclusos no 'canvas'
        while (ocupado != nullptr && ponto_de_inicio < obj_max_x) {
            
            // 2a. Se houver espaço antes do bloco ocupado, é um segmento visível
            if (ponto_de_inicio < ocupado->inicio) {
                double fim_visivel = std::min(obj_max_x, ocupado->inicio);
                
                if (fim_visivel > ponto_de_inicio) {
                    // Adiciona a parte visível aos resultados
                    insereSegmento((int)tempo_cena, obj.id_objeto, ponto_de_inicio, fim_visivel);
                }
            }
            
            // 2b. Atualiza o ponto de início para continuar a busca APÓS o bloco ocupado
            if (ocupado->fim > ponto_de_inicio) {
                ponto_de_inicio = ocupado->fim;
            }

            ocupado = ocupado->prox;
        }

        // 3. Se houver espaço APÓS o último bloco ocupado, é um segmento visível final
        if (ponto_de_inicio < obj_max_x) {
            insereSegmento((int)tempo_cena, obj.id_objeto, ponto_de_inicio, obj_max_x);
        }

        // 4. Adiciona o intervalo TOTAL deste objeto ao canvas para bloquear objetos mais distantes
        adicionaIntervaloOcupado(&canvas_ocupado, obj_min_x, obj_max_x);
        
        current_obj = current_obj->prox;
    }
    
    // Limpar a memória da lista temporária 'canvas_ocupado' (IntervaloOcupado)
    IntervaloOcupado* current_canvas = canvas_ocupado;
    IntervaloOcupado* next_canvas = nullptr;
    while (current_canvas != nullptr) {
        next_canvas = current_canvas->prox;
        delete current_canvas;
        current_canvas = next_canvas;
    }
}