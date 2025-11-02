#ifndef LISTAPARADA_H
#define LISTAPARADA_H

#include "Parada.h"

struct NoParada {
    Parada dado;
    NoParada* proximo;
    NoParada(Parada p);
};

class ListaParada {
private:
    NoParada* inicio;
    NoParada* fim;
    int tamanho;

public:
    ListaParada();
    ~ListaParada();

    void push_back(Parada p);
    Parada* get(int index); // Retorna ponteiro para a Parada
    int size() const;
    bool empty() const;
    void clear();
};

#endif // LISTAPARADA_H