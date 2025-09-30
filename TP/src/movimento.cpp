#include "movimento.hpp"


movimento::movimento(char id , int tempo , int objeto ,  int x_atualizado, int y_atualizado)
{
    this->id = id;
    this->tempo = tempo;
    this->objeto = objeto;
    this->x_atualizado = x_atualizado;
    this->y_atualizado = y_atualizado;

}