#ifndef MOVIMENTO_HPP
#endif


class movimento
{
 
public:
     
    char id = 'M';
    int tempo; 
    float objeto;
    float x_atualizado;
    float y_atualizado;
     
    
    movimento::movimento(char id , int tempo , int objeto ,  int x_atualizado, int y_atualizado);
};


#define MOVIMENTO_HPP