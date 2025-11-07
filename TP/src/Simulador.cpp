#include "Simulador.h"
#include <iostream>  
#include <fstream>   
#include <iomanip> 

Simulador::Simulador() 
    : eta(0), gama(0.0), delta(0.0), alfa(0.0), beta(0.0), lambda(0.0),
      demandasProcessadas(nullptr), numTotalDemandas(0)
{
    // Construtor
}

Simulador::~Simulador() {
    // Destrutor
    
    // CORRIGIDO (Bug do 'AS')
    for (int i = 0; i < listaDeTodasDemandas.size(); ++i) { 
        delete listaDeTodasDemandas.get(i);
    }
    
    for (int i = 0; i < listaDeTodasCorridas.size(); ++i) {
        delete listaDeTodasCorridas.get(i);
    }
    if (demandasProcessadas != nullptr) {
        delete[] demandasProcessadas;
    }
}

// MODIFICADO: Aceita um std::istream& genérico
void Simulador::carregarEntrada(std::istream& input) { 
    
    // Não precisamos mais abrir ou fechar o arquivo,
    // apenas ler do 'input' (que pode ser cin ou um fstream).
    
    // 1-6: Lê os parâmetros
    input >> this->eta;
    input >> this->gama;
    input >> this->delta;
    input >> this->alfa;
    input >> this->beta;
    input >> this->lambda;

    // 7: Lê o número de demandas
    input >> this->numTotalDemandas;
    
    this->demandasProcessadas = new bool[numTotalDemandas];
    
    // --- CORREÇÃO DO VALGRIND (Bug 1) ---
    // Inicializa o array de booleanos
    for (int i = 0; i < numTotalDemandas; ++i) {
        demandasProcessadas[i] = false;
    }
    // --- FIM DA CORREÇÃO ---

    // Loop para ler todas as demandas
    for (int i = 0; i < numTotalDemandas; ++i) {
        int id, tempo;
        double ox, oy, dx, dy;
        
        input >> id >> tempo >> ox >> oy >> dx >> dy; 
        
        Coordenada origem(ox, oy);
        Coordenada destino(dx, dy);
        
        Demanda* novaDemanda = new Demanda(id, tempo, origem, destino);
        listaDeTodasDemandas.push_back(novaDemanda);
    }
    
    // Configura a precisão da saída
    std::cout << std::fixed << std::setprecision(2);
}

void Simulador::processarDemandas() {
    // --- FASE 1: Construção das Corridas ---
    
    for (int i = 0; i < numTotalDemandas; ++i) {
        if (demandasProcessadas[i]) continue; // Agora é seguro

        Demanda* c0 = listaDeTodasDemandas.get(i);
        demandasProcessadas[i] = true; 

        Corrida* novaCorrida = new Corrida(this->gama);
        novaCorrida->adicionarDemanda(c0); 
        
        for (int j = i + 1; j < numTotalDemandas; ++j) {
            if (demandasProcessadas[j]) continue;

            Demanda* ci = listaDeTodasDemandas.get(j);

            if (ci->tempo - c0->tempo >= this->delta) break; 
            if (novaCorrida->demandasAtendidas.size() >= this->eta) break; 

            bool origensOk = true;
            for (int k = 0; k < novaCorrida->demandasAtendidas.size(); ++k) {
                if (ci->origem.distancia(novaCorrida->demandasAtendidas.get(k)->origem) >= this->alfa) {
                    origensOk = false;
                    break;
                }
            }
            if (!origensOk) break; 

            bool destinosOk = true;
            for (int k = 0; k < novaCorrida->demandasAtendidas.size(); ++k) {
                if (ci->destino.distancia(novaCorrida->demandasAtendidas.get(k)->destino) >= this->beta) {
                    destinosOk = false;
                    break;
                }
            }
            if (!destinosOk) break;

            novaCorrida->adicionarDemanda(ci); 
            if (novaCorrida->eficiencia <= this->lambda) {
                novaCorrida->removerUltimaDemanda();
                break; 
            } else {
                demandasProcessadas[j] = true;
            }
        } 

        listaDeTodasCorridas.push_back(novaCorrida);

        if (novaCorrida->trechos.size() > 0) {
            Trecho& primeiroTrecho = novaCorrida->trechos.get(0);
            double tempoInicio = novaCorrida->demandasAtendidas.get(0)->tempo;
            double tempoChegada = tempoInicio + primeiroTrecho.tempoGasto;
            
            Evento* primeiroEvento = new Evento(tempoChegada, CHEGADA_PARADA, novaCorrida, 0);
            heap.inserir(primeiroEvento);
        }
    } 
}

void Simulador::executar() {
    // --- FASE 2: Loop de Simulação ---
    
    while (!heap.estaVazio()) {
        Evento* eventoAtual = heap.removerMin(); 
        
        // Versão de 1 argumento para o VPL
        processarEvento(eventoAtual); 
        
        delete eventoAtual; 
    }
}

// Versão de 1 argumento (para o VPL)
void Simulador::processarEvento(Evento* evento) { 
    Corrida* corrida = evento->corrida;
    int indiceTrechoConcluido = evento->indiceTrecho;

    if (indiceTrechoConcluido == corrida->trechos.size() - 1) {
        // --- É O ÚLTIMO EVENTO DA CORRIDA ---
        
        std::cout << evento->tempo << " ";
        std::cout << corrida->distanciaTotal << " ";
        std::cout << corrida->numeroParadas << " ";

        std::cout << corrida->trechos.get(0).paradaOrigem->localizacao.x << " "
                  << corrida->trechos.get(0).paradaOrigem->localizacao.y;
                  
        for (int i = 0; i < corrida->trechos.size(); ++i) {
            std::cout << " " << corrida->trechos.get(i).paradaDestino->localizacao.x
                      << " " << corrida->trechos.get(i).paradaDestino->localizacao.y;
        }

        // Imprime o std::endl (necessário para o VPL)
        std::cout << std::endl; 

    } else {
        // --- NÃO É O ÚLTIMO EVENTO ---
        
        int indiceProximoTrecho = indiceTrechoConcluido + 1;
        
        // --- CORREÇÃO DO BUG DE LÓGICA ---
        Trecho& proximoTrecho = corrida->trechos.get(indiceProximoTrecho); // CORRIGIDO
        
        double tempoProximoEvento = evento->tempo + proximoTrecho.tempoGasto;
        
        Evento* proximoEvento = new Evento(
            tempoProximoEvento,
            CHEGADA_PARADA,
            corrida,
            indiceProximoTrecho
        );
        
        heap.inserir(proximoEvento);
    }
}