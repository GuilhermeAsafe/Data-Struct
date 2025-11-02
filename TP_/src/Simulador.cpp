#include "Simulador.h"
#include "Corrida.h"
#include <iostream>
#include <fstream>
#include <sstream>

Simulador::Simulador() {
    // Construtor
}

void Simulador::carregarEntrada(const char* nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Erro: Não foi possível abrir o arquivo de entrada: " << nomeArquivo << std::endl;
        return;
    }

    std::string linha;
    int numDemandas;

    // 1-6: Lê os parâmetros
    arquivo >> this->eta;
    arquivo >> this->gama;
    arquivo >> this->delta;
    arquivo >> this->alfa;
    arquivo >> this->beta;
    arquivo >> this->lambda;

    // 7: Lê o número de demandas
    arquivo >> numDemandas;
    
    // Loop para ler todas as demandas
    for (int i = 0; i < numDemandas; ++i) {
        int id, tempo, ox, oy, dx, dy;
        arquivo >> id >> tempo >> ox >> oy >> dx >> dy;
        
        Coordenada origem(ox, oy);
        Coordenada destino(dx, dy);
        
        // Aloca dinamicamente a Demanda
        Demanda* novaDemanda = new Demanda(id, tempo, origem, destino);
        
        // Adiciona na lista
        listaDeTodasDemandas.push_back(novaDemanda);
    }
    
    arquivo.close();
}

void Simulador::processarDemandas() {
    // --- TODO: IMPLEMENTAR FASE 1 ---
    // Esta é a lógica de agrupamento de corridas [cite: 915-925].
    //
    // Para cada demanda C0 em 'listaDeTodasDemandas':
    // 1. Crie uma nova Corrida (alocada dinamicamente, ex: new Corrida())
    // 2. Tente adicionar C1, C2... à Corrida,
    //    verificando os critérios (delta, alfa, beta, lambda, eta).
    // 3. Quando a Corrida estiver pronta (individual ou combinada):
    //    - Gere a sequência de paradas e trechos dela.
    //    - Crie o PRIMEIRO Evento (ex: chegada na primeira parada).
    //    - escalonador.InsereEvento(primeiroEvento);
    
    std::cout << "Aviso: Fase 1 (processarDemandas) não implementada." << std::endl;
}

void Simulador::executar() {
    // --- FASE 2: Loop de Simulação ---
    // [cite: 927-930]
    
    while (!escalonador.estaVazio()) {
        // 1. Pega o próximo evento
        Evento* eventoAtual = escalonador.RetiraProximoEvento();
        
        // 2. Processa o evento
        processarEvento(eventoAtual);
        
        // 3. O evento processado é nosso, devemos deletá-lo
        delete eventoAtual;
    }
}

void Simulador::processarEvento(Evento* evento) {
    Corrida* corrida = evento->corrida;
    int indiceTrechoConcluido = evento->indiceTrecho;

    // TODO: Processar o que acontece no evento (ex: atualizar estado da demanda)
    
    // Verifica se este foi o ÚLTIMO trecho/parada da corrida
    if (indiceTrechoConcluido == corrida->trechos.size() - 1) {
        // --- É O ÚLTIMO EVENTO DA CORRIDA ---
        // 2. Se for o último, gere as estatísticas [cite: 929]
        // [cite: 1022-1030]
        
        std::cout << evento->tempo << " "; // 1. Tempo de conclusão
        std::cout << corrida->distanciaTotal << " "; // 2. Distância
        std::cout << corrida->numeroParadas << " "; // 3. Número de paradas
        
        // 4. Sequência de coordenadas
        // (Você precisa implementar a lógica para imprimir as paradas)
        std::cout << std::endl;

        // Limpa a memória da corrida
        // (Isso depende de como você gerencia o ciclo de vida da Corrida)
        // delete corrida; 
        
    } else {
        // --- NÃO É O ÚLTIMO EVENTO ---
        // 3. Senão, escalone o próximo evento [cite: 930]
        
        // Pega o próximo trecho
        int indiceProximoTrecho = indiceTrechoConcluido + 1;
        Trecho& proximoTrecho = corrida->trechos.get(indiceProximoTrecho);
        
        // Calcula o tempo de chegada
        double tempoProximoEvento = evento->tempo + proximoTrecho.tempoGasto;
        
        // Cria o novo evento
        Evento* proximoEvento = new Evento(
            tempoProximoEvento,
            CHEGADA_PARADA,
            corrida,
            indiceProximoTrecho
        );
        
        // Insere no escalonador
        escalonador.InsereEvento(proximoEvento);
    }
}