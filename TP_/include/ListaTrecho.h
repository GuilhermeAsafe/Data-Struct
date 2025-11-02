#ifndef LISTATRECHO_H
#define LISTATRECHO_H

#include "Trecho.h" // Precisa saber o que é Trecho

// O Nó da lista, armazena o Trecho por valor
struct NoTrecho {
    Trecho dado;
    NoTrecho* proximo;

    NoTrecho(Trecho t);
};

// A Lista Encadeada que gerencia os Nós
class ListaTrecho {
private:
    NoTrecho* inicio;
    NoTrecho* fim; 
    int tamanho;

public:
    ListaTrecho();
    ~ListaTrecho(); // Destrutor para limpar os nós

    void push_back(Trecho t);
    Trecho& get(int index); // Retorna referência para o Trecho
    int size() const;
    bool empty() const;
    
    // Limpa a lista (deleta os nós)
    void clear(); 
};

#endif // LISTATRECHO_H