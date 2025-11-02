#ifndef EVENTO_H
#define EVENTO_H

class Corrida;

enum TipoEvento {
    CHEGADA_PARADA
};

class Evento {
public:
    double tempo;      // Chave da fila de prioridade
    TipoEvento tipo;
    Corrida* corrida;
    int indiceTrecho; // Qual trecho da corrida está sendo concluído (0, 1, 2...)

    Evento(double t, TipoEvento tp, Corrida* c, int indice);

    /**
     * Compara dois eventos.
     * Retorna TRUE se this->tempo > outro.tempo
     */
    bool operator>(const Evento& outro) const;
};

#endif // EVENTO_H