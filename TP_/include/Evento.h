#ifndef EVENTO_H
#define EVENTO_H

// Encaminhar declarações para evitar inclusão circular
class Corrida;

// Define os tipos de eventos da simulação
enum TipoEvento {
    CHEGADA_PARADA // Único tipo necessário: chegada em uma parada (embarque ou desembarque)
};

class Evento {
public:
    double tempo;      // O tempo em que o evento ocorre (chave da fila de prioridade)
    TipoEvento tipo;
    Corrida* corrida;  // A qual corrida este evento pertence
    int indiceTrecho; // Qual trecho da corrida está sendo concluído (ex: 0, 1, 2...)

    /**
     * Construtor do Evento.
     * @param t Tempo de ocorrência
     * @param tp Tipo do evento
     * @param c Ponteiro para a corrida associada
     * @param indice Índice do trecho/parada que será processado
     */
    Evento(double t, TipoEvento tp, Corrida* c, int indice);

    /**
     * Sobrecarga do operador '>' para o MinHeap poder comparar Eventos.
     * Um evento é "maior" se seu tempo de ocorrência for maior.
     */
    bool operator>(const Evento& outro) const;
};

#endif // EVENTO_H