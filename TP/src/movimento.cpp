#include "include/movimento.hpp"
#include "include/lista.hpp"
#include "include/objeto.hpp"

#include <iostream>
 
/**
 * @brief Construtor da classe movimento.
 */
movimento::movimento(char id , double tempo , double objeto ,  double x_atualizado, double y_atualizado)
{
    this->id = id;
    this->tempo = tempo;
    this->objeto = objeto;
    this->x_atualizado = x_atualizado;
    this->y_atualizado = y_atualizado;
}

/**
 * @brief Atualiza a posição de um objeto na lista principal.
 * @param minha_lista A lista de objetos a ser modificada.
 */
void movimento::movimentar(listas& minha_lista)
{
    try {
        // 1. Busca o objeto pelo ID e obtém a referência direta ao objeto na lista.
        objetos& obj_para_mover = minha_lista.busca(objeto);
        
        // 2. Altera os campos do objeto na lista usando a referência.
        obj_para_mover.x = x_atualizado;
        obj_para_mover.y = y_atualizado;

    } catch (const std::runtime_error& e) {
        // Trata a exceção caso o objeto com o ID especificado não seja encontrado.
        std::cerr << "Falha na movimentação: " << e.what() << std::endl;
    }
}