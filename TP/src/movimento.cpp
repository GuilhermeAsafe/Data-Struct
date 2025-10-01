#include "movimento.hpp"
#include "lista.hpp"

#include <iostream>
 


movimento::movimento(char id , int tempo , int objeto ,  int x_atualizado, int y_atualizado)
{
    this->id = id;
    this->tempo = tempo;
    this->objeto = objeto;
    this->x_atualizado = x_atualizado;
    this->y_atualizado = y_atualizado;

}

//precisamos chamar o metode de busca que esta no lista.cpp

void movimento::movimentar(int tempo, float objeto, float x_atualizado, float y_atualizado)
{

   listas minha_lista;
    minha_lista.busca(objeto);
    

}

