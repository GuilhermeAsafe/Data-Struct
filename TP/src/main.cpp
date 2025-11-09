#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

#include "TADs.h"
#include "Model.h"

int main() {
    std::cout.precision(2);
    std::cout << std::fixed;

    Simulador sim;
    std::string linha;

    std::getline(std::cin, linha);
    std::stringstream ss_eta(linha);
    ss_eta >> sim.eta;

    std::getline(std::cin, linha);
    std::stringstream ss_gama(linha);
    ss_gama >> sim.gama;

    std::getline(std::cin, linha);
    std::stringstream ss_delta(linha);
    ss_delta >> sim.delta;

    std::getline(std::cin, linha);
    std::stringstream ss_alfa(linha);
    ss_alfa >> sim.alfa;

    std::getline(std::cin, linha);
    std::stringstream ss_beta(linha);
    ss_beta >> sim.beta;

    std::getline(std::cin, linha);
    std::stringstream ss_lambda(linha);
    ss_lambda >> sim.lambda;

    std::getline(std::cin, linha);
    std::stringstream ss_num(linha);
    int numdemandas;
    ss_num >> numdemandas;

    for (int i = 0; i < numdemandas; ++i) {
        Demanda* d = new Demanda();
        
        if (!(std::cin >> d->id >> d->tempo 
                       >> d->origem.x >> d->origem.y 
                       >> d->destino.x >> d->destino.y)) {
            
            delete d;
            break;
        }
        
        d->estado = 1;
        sim.demandas.insere(d);
    }

    sim.run();

    return 0;
}