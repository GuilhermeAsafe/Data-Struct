#ifndef LISTADEMANDA_H
#define LISTADEMANDA_H

#include "Demanda.h" // Precisa saber o que é Demanda*

// O Nó da lista, armazena um ponteiro para a Demanda
struct NoDemanda {
    Demanda* dado;
    NoDemanda* proximo;

    NoDemanda(Demanda* d);
};

// A Lista Encadeada que gerencia os Nós
class ListaDemanda {
private:
    NoDemanda* inicio;
    NoDemanda* fim; // Para otimizar push_back (O(1))
    int tamanho;

public:
    ListaDemanda();
    ~ListaDemanda(); // Destrutor para limpar os nós

    void push_back(Demanda* d);
    Demanda* get(int index);
    int size() const;
    bool empty() const;
    
    // Limpa a lista (deleta os nós, mas não as demandas)
    void clear(); 
};

#endif // LISTADEMANDA_H