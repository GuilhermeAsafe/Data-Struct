#ifndef LISTADEMANDA_H
#define LISTADEMANDA_H

#include "Demanda.h"

struct NoDemanda {
    Demanda* dado;
    NoDemanda* proximo;
    NoDemanda(Demanda* d);
};

class ListaDemanda {
private:
    NoDemanda* inicio;
    NoDemanda* fim;
    int tamanho;

public:
    ListaDemanda();
    ~ListaDemanda();

    void push_back(Demanda* d);
    Demanda* get(int index);
    Demanda* pop_back(); // Remove e retorna o último
    int size() const;
    bool empty() const;
    void clear(); 
};

#endif // LISTADEMANDA_H