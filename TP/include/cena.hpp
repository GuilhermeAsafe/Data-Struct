#ifndef CENA_HPP
#define CENA_HPP

#include "include/lista.hpp"

class Cena
{

private:

    struct Node_cena
    {
        
        listas minha_lista;

        Node_cena* prox;

        Node_cena(listas minha_lista) : minha_lista(minha_lista), prox(nullptr) {}

    };

    Node_cena* head = nullptr;
    Node_cena* tail =  nullptr;

    

public:

    void geraCena ( o b j e t o _ t ∗ vobj , int numobj ,
cena_t ∗ cena , int numcena ) {
OrdenaPorY ( vobj , numobj ) ;
for ( int i =0; i <numobj ; i ++){
i f ( o b j e t o V i s i v e l ( vobj [ i ] ) ) {
a d i c i o n a O b j ( vo bj [ i ] , cena ,&numcena ) ;

};

#endif