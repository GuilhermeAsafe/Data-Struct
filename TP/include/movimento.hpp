#ifndef MOVIMENTO_HPP
#endif

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

    void movimentar(listas& minha_lista,float tempo, float objeto, float x_atualizado, float y_atualizado);
};


#define MOVIMENTO_HPP