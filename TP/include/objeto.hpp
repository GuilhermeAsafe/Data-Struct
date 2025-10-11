#ifndef OBJETOS_HPP
#define OBJETOS_HPP

//minha classe deve ser um ponteiro, como faço isso?
//devo criar um vetor de objetos?
//devo criar uma classe que armazene os dados de entrada? 

//RESPOSTA: Vou implementar um TAD que armazene os dados de entrada. 


class objetos
{

public:

    char id = 'O';
    double id_objeto;
    double x;
    double y;
    double largura;
    
    objetos(char id , double id_objeto , double x ,  double y , double largura);
    
};

#endif