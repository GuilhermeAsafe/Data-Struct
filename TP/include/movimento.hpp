#ifndef MOVIMENTO_HPP
#define MOVIMENTO_HPP

#include "include/lista.hpp"

class movimento
{
 
public:
     
    char id = 'M';
    double tempo; 
    double objeto;
    double x_atualizado;
    double y_atualizado;
     
    
    movimento(char id ,double tempo , double objeto ,  double x_atualizado, double y_atualizado);

    void movimentar(listas& minha_lista);
};

#endif
 