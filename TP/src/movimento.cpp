#include "include/movimento.hpp"
#include "include/lista.hpp"
#include "include/objeto.hpp"

#include <iostream>
 


movimento::movimento(char id , double tempo , double objeto ,  double x_atualizado, double y_atualizado)
{
    this->id = id;
    this->tempo = tempo;
    this->objeto = objeto;
    this->x_atualizado = x_atualizado;
    this->y_atualizado = y_atualizado;

}

//precisamos chamar o metode de busca que esta no lista.cpp

void movimento::movimentar(listas& minha_lista)
{
    try {
        // 1. Chama busca() e armazena a referência para o objeto na lista.
        // Qualquer alteração em 'obj_para_mover' altera o objeto dentro de 'minha_lista'.
        objetos& obj_para_mover = minha_lista.busca(objeto);
        
        // 2. Altera os campos do objeto diretamente usando a referência.
        obj_para_mover.x = x_atualizado;
        obj_para_mover.y = y_atualizado;

        // Note que o campo 'objeto' na classe movimento é o ID,
        // mas você está usando 'x_atualizado' e 'y_atualizado' como double.

    } catch (const std::runtime_error& e) {
        // Trata o erro caso o objeto não seja encontrado.
        std::cerr << "Falha na movimentação: " << e.what() << std::endl;
    }
}


