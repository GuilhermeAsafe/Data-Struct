#ifndef LISTATRECHO_H
#define LISTATRECHO_H

#include "Trecho.h"

struct NoTrecho {
    Trecho dado;
    NoTrecho* proximo;
    NoTrecho(Trecho t);
};

class ListaTrecho {
private:
    NoTrecho* inicio;
    NoTrecho* fim; 
    int tamanho;

public:
    ListaTrecho();
    ~ListaTrecho();

    void push_back(Trecho t);
    Trecho& get(int index);
    int size() const;
    bool empty() const;
    void clear(); 
};

#endif // LISTATRECHO_H