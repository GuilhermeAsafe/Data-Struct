#ifndef LISTACORRIDA_H
#define LISTACORRIDA_H

// Encaminhar declaração
class Corrida;

struct NoCorrida {
    Corrida* dado;
    NoCorrida* proximo;
    NoCorrida(Corrida* c);
};

class ListaCorrida {
private:
    NoCorrida* inicio;
    NoCorrida* fim;
    int tamanho;

public:
    ListaCorrida();
    ~ListaCorrida();

    void push_back(Corrida* c);
    Corrida* get(int index);
    int size() const;
    bool empty() const;
    void clear(); 
};

#endif // LISTACORRIDA_H