#include "Model.h"
#include <cmath>

double calcularDistancia(Coordenada c1, Coordenada c2) {
    double dx = c1.x - c2.x;
    double dy = c1.y - c2.y;
    return sqrt(dx * dx + dy * dy);
}