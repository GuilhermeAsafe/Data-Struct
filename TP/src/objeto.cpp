#include "include/objeto.hpp"

objetos::objetos(char id , float centro_objeto , float x ,  float y , float largura)
{
    this->id = id;
    this->id_objeto = centro_objeto;
    this->x = x;
    this->y = y;
    this->largura = largura;
}

//objeto::objeto(char id , int centro_obeto , int x ,  int y , int largura) : 
//id(id), centro_obeto(centro_obeto), x(x), y(y), largura(largura) {}