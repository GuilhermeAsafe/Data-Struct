#include "Simulador.h"
#include "Corrida.h"
#include <iostream>
#include <fstream>
#include <iomanip> // Para std::setprecision

Simulador::Simulador() 
    : eta(0), gama(0.0), delta(0.0), alfa(0.0), beta(0.0), lambda(0.0),
      demandasProcessadas(nullptr), numTotalDemandas(0)
{
    // Construtor
}

Simulador::~Simulador() {
    // Destrutor: Limpa toda a memória alocada dinamicamente
    
    // 1. Deleta todas as Demandas
    for (int i = 0; i < listaDeTodasDemandas.size(); ++i) {
        delete listaDeTodasDemandas.get(i);
    }
    
    // 2. Deleta todas as Corridas
    for (int i = 0; i < listaDeTodasCorridas.size(); ++i) {
        delete listaDeTodasCorridas.get(i);
    }

    // 3. Deleta o array de booleanos
    if (demandasProcessadas != nullptr) {
        delete[] demandasProcessadas;
    }
}

void Simulador::carregarEntrada(const char* nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Erro: Não foi possível abrir o arquivo de entrada: " << nomeArquivo << std::endl;
        return;
    }

    // 1-6: Lê os parâmetros
    arquivo >> this->eta;
    arquivo >> this->gama;
    arquivo >> this->delta;
    arquivo >> this->alfa;
    arquivo >> this->beta;
    arquivo >> this->lambda;

    // 7: Lê o número de demandas
    arquivo >> this->numTotalDemandas;
    
    // Prepara o array de controle
    this->demandasProcessadas = new bool[numTotalDemandas];
    for (int i = 0; i < numTotalDemandas; ++i) {
        demandasProcessadas[i] = false;
    }

    // Loop para ler todas as demandas
    for (int i = 0; i < numTotalDemandas; ++i) {
        int id, tempo, ox, oy, dx, dy;
        arquivo >> id >> tempo >> ox >> oy >> dx >> dy;
        
        Coordenada origem(ox, oy);
        Coordenada destino(dx, dy);
        
        Demanda* novaDemanda = new Demanda(id, tempo, origem, destino);
        listaDeTodasDemandas.push_back(novaDemanda);
    }
    
    arquivo.close();
    
    // Configura a precisão da saída de ponto flutuante para 2 casas decimais
    std::cout << std::fixed << std::setprecision(2);
}

void Simulador::processarDemandas() {
    // --- FASE 1: Construção das Corridas ---
    // Implementa o algoritmo da Seção 1
    
    for (int i = 0; i < numTotalDemandas; ++i) {
        
        if (demandasProcessadas[i]) {
            continue;
        }

        Demanda* c0 = listaDeTodasDemandas.get(i);
        demandasProcessadas[i] = true; 

        Corrida* novaCorrida = new Corrida(this->gama);
        novaCorrida->adicionarDemanda(c0); 
        
        // Tenta combinar com as próximas demandas
        for (int j = i + 1; j < numTotalDemandas; ++j) {
            
            if (demandasProcessadas[j]) {
                continue;
            }

            Demanda* ci = listaDeTodasDemandas.get(j);

            // 1. Critério de Tempo (delta)
            if (ci->tempo - c0->tempo >= this->delta) {
                break; // Interrompe verificação (demandas estão ordenadas)
            }

            // 2. Critério de Capacidade (eta)
            if (novaCorrida->demandasAtendidas.size() >= this->eta) {
                break; // Interrompe verificação (corrida cheia)
            }

            // 3. Critério de Origens (alfa)
            bool origensOk = true;
            for (int k = 0; k < novaCorrida->demandasAtendidas.size(); ++k) {
                Demanda* ck = novaCorrida->demandasAtendidas.get(k);
                if (ci->origem.distancia(ck->origem) >= this->alfa) {
                    origensOk = false;
                    break;
                }
            }
            if (!origensOk) {
                // CORREÇÃO: O PDF diz para "interrompa a avaliação"
                break; 
            }

            // 4. Critério de Destinos (beta)
            bool destinosOk = true;
            for (int k = 0; k < novaCorrida->demandasAtendidas.size(); ++k) {
                Demanda* ck = novaCorrida->demandasAtendidas.get(k);
                if (ci->destino.distancia(ck->destino) >= this->beta) {
                    destinosOk = false;
                    break;
                }
            }
            if (!destinosOk) {
                // CORREÇÃO: O PDF diz para "interrompa a avaliação"
                break;
            }

            // 5. Critério de Eficiência (lambda)
            novaCorrida->adicionarDemanda(ci); // Adiciona temporariamente

            // O critério é eficiencia > lambda.
            // Se for <=, falha.
            if (novaCorrida->eficiencia <= this->lambda) {
                // Falhou: remove e interrompe
                novaCorrida->removerUltimaDemanda();
                break; // Interrompe a avaliação desta corrida
            } else {
                // Sucesso: marca ci como processada
                demandasProcessadas[j] = true;
            }
        } // Fim do loop 'j' (tentativa de combinação)

        listaDeTodasCorridas.push_back(novaCorrida);

        // 6. Agendamento do primeiro evento
        if (novaCorrida->trechos.size() > 0) {
            Trecho& primeiroTrecho = novaCorrida->trechos.get(0);
            
            double tempoInicio = novaCorrida->demandasAtendidas.get(0)->tempo;
            
            // *** GARANTA QUE ESTA LINHA USA .tempoGasto ***
            double tempoChegada = tempoInicio + primeiroTrecho.tempoGasto;
            
            Evento* primeiroEvento = new Evento(
                tempoChegada,
                CHEGADA_PARADA,
                novaCorrida,
                0 // Índice do primeiro trecho (trecho 0)
            );
            
            escalonador.InsereEvento(primeiroEvento);
        }
    } // Fim do loop 'i' (processamento de demandas)
}

void Simulador::executar() {
    // --- FASE 2: Loop de Simulação ---
    //
    
    while (!escalonador.estaVazio()) {
        Evento* eventoAtual = escalonador.RetiraProximoEvento();
        processarEvento(eventoAtual);
        delete eventoAtual; 
    }
}

void Simulador::processarEvento(Evento* evento) {
    Corrida* corrida = evento->corrida;
    int indiceTrechoConcluido = evento->indiceTrecho;

    // Verifica se este foi o ÚLTIMO trecho/parada da corrida
    if (indiceTrechoConcluido == corrida->trechos.size() - 1) {
        // --- É O ÚLTIMO EVENTO DA CORRIDA ---
        // 1. Gera as estatísticas e imprime a saída
        
        // 1. Tempo de conclusão
        std::cout << evento->tempo << " ";
        // 2. Distância total
        std::cout << corrida->distanciaTotal << " ";
        // 3. Número de paradas
        std::cout << corrida->numeroParadas << " ";

        // 4. Sequência de coordenadas
        // CORREÇÃO: Cast para (double) para formatar a saída
        
        std::cout << static_cast<double>(corrida->trechos.get(0).paradaOrigem->localizacao.x) << " "
                  << static_cast<double>(corrida->trechos.get(0).paradaOrigem->localizacao.y);
                  
        for (int i = 0; i < corrida->trechos.size(); ++i) {
            std::cout << " " << static_cast<double>(corrida->trechos.get(i).paradaDestino->localizacao.x)
                      << " " << static_cast<double>(corrida->trechos.get(i).paradaDestino->localizacao.y);
        }
        std::cout << std::endl; // Fim da linha de saída

    } else {
        // --- NÃO É O ÚLTIMO EVENTO ---
        // 3. Senão, escalone o próximo evento
        
        int indiceProximoTrecho = indiceTrechoConcluido + 1;
        Trecho& proximoTrecho = corrida->trechos.get(indiceProximoTrecho);
        
        double tempoProximoEvento = evento->tempo + proximoTrecho.tempoGasto;
        
        Evento* proximoEvento = new Evento(
            tempoProximoEvento,
            CHEGADA_PARADA,
            corrida,
            indiceProximoTrecho
        );
        
        escalonador.InsereEvento(proximoEvento);
    }
}