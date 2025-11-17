#include "Model.h"
#include <cmath> // Para a função sqrt (raiz quadrada)

// Calcula a distância Euclidiana real entre duas coordenadas.
double calcularDistancia(Coordenada c1, Coordenada c2) {
    double dx = c1.x - c2.x;
    double dy = c1.y - c2.y;
    // Retorna a raiz quadrada da soma dos quadrados (Pitágoras)
    return sqrt(dx * dx + dy * dy);
}