#ifndef COORDENADA_H
#define COORDENADA_H

#include <cmath> // Para usar sqrt() no cálculo da distância

// Struct simples para armazenar coordenadas X e Y
struct Coordenada {
    int x;
    int y;

    // Construtor padrão
    Coordenada(int x_val = 0, int y_val = 0) : x(x_val), y(y_val) {}

    /**
     * Calcula a distância Euclidiana entre esta coordenada e outra.
     */
    double distancia(const Coordenada& outra) const {
        return std::sqrt(std::pow(this->x - outra.x, 2) + std::pow(this->y - outra.y, 2));
    }
};

#endif // COORDENADA_H