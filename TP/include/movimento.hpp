#ifndef MOVIMENTO_HPP
#define MOVIMENTO_HPP

#include "include/lista.hpp"

class movimento
{
 
public:
     
    char id = 'M';
    float tempo; 
    float objeto;
    float x_atualizado;
    float y_atualizado;
     
    
    movimento(char id ,float tempo , float objeto ,  float x_atualizado, float y_atualizado);

    void movimentar(listas& minha_lista);
};

#endif
 