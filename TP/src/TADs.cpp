#include "TADs.h"
#include "Model.h"
#include <iostream>
#include <stdexcept> // Para std::runtime_error (Robustez)
#include <cmath>     // Para fabs (valor absoluto)

// ===================================================================
// --- Implementação da ListaBase ---
// ===================================================================

ListaBase::ListaBase() {
    capacidade = 2; // Capacidade inicial pequena para economizar memória
    tamanho = 0;
}

int ListaBase::getTamanho() {
    return tamanho;
}

bool ListaBase::estaVazia() {
    return tamanho == 0;
}

// ===================================================================
// --- Implementação da ListaInt ---
// ===================================================================

ListaInt::ListaInt() : ListaBase() {
    // 'new' pode falhar (falta de memória), o que lança std::bad_alloc.
    // Isso é capturado pelo 'try-catch' no main.cpp (Robustez).
    dados = new int[capacidade];
}

ListaInt::~ListaInt() {
    delete[] dados; // Libera a memória alocada
}

// Lógica de redimensionamento: dobra a capacidade.
void ListaInt::redimensiona() {
    capacidade *= 2;
    int* novosDados = new int[capacidade]; // Aloca novo array
    for (int i = 0; i < tamanho; ++i) {
        novosDados[i] = dados[i]; // Copia dados antigos
    }
    delete[] dados; // Libera array antigo
    dados = novosDados; // Aponta para o novo array
}

void ListaInt::insere(int item) {
    if (tamanho == capacidade) {
        redimensiona(); // Garante que há espaço
    }
    dados[tamanho] = item;
    tamanho++;
}

/**
 * [ROBUSTO] Acessa o item no índice 'i' com verificação de limites.
 * Se o índice for inválido, lança uma exceção para parar o programa
 * de forma controlada, em vez de causar uma "falha de segmentação".
 */
int ListaInt::get(int i) {
    // Programação Defensiva: verifica se o índice está nos limites válidos
    if (i < 0 || i >= tamanho) {
        // Lança uma exceção que será capturada pelo 'try-catch' no main.cpp
        throw std::runtime_error("Erro [ListaInt]: Indice de acesso invalido.");
    }
    return dados[i];
}

void ListaInt::removeUltimo() {
    if (tamanho > 0) {
        tamanho--; // Remoção "barata"
    }
}

void ListaInt::limpa() {
    tamanho = 0; // Apenas reseta o contador (reutiliza a memória alocada)
}

// ===================================================================
// --- Implementação da ListaDemandaPtr ---
// (A lógica é idêntica à ListaInt, mas para ponteiros Demanda**)
// ===================================================================

ListaDemandaPtr::ListaDemandaPtr() : ListaBase() {
    dados = new Demanda*[capacidade];
}

ListaDemandaPtr::~ListaDemandaPtr() {
    delete[] dados;
}

void ListaDemandaPtr::redimensiona() {
    capacidade *= 2;
    Demanda** novosDados = new Demanda*[capacidade];
    for (int i = 0; i < tamanho; ++i) {
        novosDados[i] = dados[i];
    }
    delete[] dados;
    dados = novosDados;
}

void ListaDemandaPtr::insere(Demanda* item) {
    if (tamanho == capacidade) {
        redimensiona();
    }
    dados[tamanho] = item;
    tamanho++;
}

/**
 * [ROBUSTO] Acessa o item no índice 'i' com verificação de limites.
 */
Demanda* ListaDemandaPtr::get(int i) {
    if (i < 0 || i >= tamanho) {
        throw std::runtime_error("Erro [ListaDemandaPtr]: Indice de acesso invalido.");
    }
    return dados[i];
}

/**
 * [ROBUSTO] Define o item no índice 'i' com verificação de limites.
 */
void ListaDemandaPtr::set(int i, Demanda* item) {
    // Programação Defensiva
    if (i < 0 || i >= tamanho) {
        throw std::runtime_error("Erro [ListaDemandaPtr]: Indice de SET invalido.");
    }
    dados[i] = item;
}

// Limpa a lista. Se 'deletaPonteiros' for true, libera a memória
// de cada Demanda apontada.
void ListaDemandaPtr::limpa(bool deletaPonteiros) {
    if (deletaPonteiros) {
        for (int i = 0; i < tamanho; ++i) {
            delete dados[i];
        }
    }
    tamanho = 0;
}

// ===================================================================
// --- Implementação da ListaParadaPtr ---
// (Lógica idêntica à ListaDemandaPtr, mas para Parada**)
// ===================================================================

ListaParadaPtr::ListaParadaPtr() : ListaBase() {
    dados = new Parada*[capacidade];
}

ListaParadaPtr::~ListaParadaPtr() {
    delete[] dados;
}

void ListaParadaPtr::redimensiona() {
    capacidade *= 2;
    Parada** novosDados = new Parada*[capacidade];
    for (int i = 0; i < tamanho; ++i) {
        novosDados[i] = dados[i];
    }
    delete[] dados;
    dados = novosDados;
}

void ListaParadaPtr::insere(Parada* item) {
    if (tamanho == capacidade) {
        redimensiona();
    }
    dados[tamanho] = item;
    tamanho++;
}

/**
 * [ROBUSTO] Acessa o item no índice 'i' com verificação de limites.
 */
Parada* ListaParadaPtr::get(int i) {
    if (i < 0 || i >= tamanho) {
        throw std::runtime_error("Erro [ListaParadaPtr]: Indice de acesso invalido.");
    }
    return dados[i];
}

void ListaParadaPtr::limpa(bool deletaPonteiros) {
    if (deletaPonteiros) {
        for (int i = 0; i < tamanho; ++i) {
            delete dados[i];
        }
    }
    tamanho = 0;
}

// ===================================================================
// --- Implementação da ListaTrechoPtr ---
// (Lógica idêntica, mas para Trecho**)
// ===================================================================

ListaTrechoPtr::ListaTrechoPtr() : ListaBase() {
    dados = new Trecho*[capacidade];
}

ListaTrechoPtr::~ListaTrechoPtr() {
    delete[] dados;
}

void ListaTrechoPtr::redimensiona() {
    capacidade *= 2;
    Trecho** novosDados = new Trecho*[capacidade];
    for (int i = 0; i < tamanho; ++i) {
        novosDados[i] = dados[i];
    }
    delete[] dados;
    dados = novosDados;
}

void ListaTrechoPtr::insere(Trecho* item) {
    if (tamanho == capacidade) {
        redimensiona();
    }
    dados[tamanho] = item;
    tamanho++;
}

/**
 * [ROBUSTO] Acessa o item no índice 'i' com verificação de limites.
 */
Trecho* ListaTrechoPtr::get(int i) {
    if (i < 0 || i >= tamanho) {
        throw std::runtime_error("Erro [ListaTrechoPtr]: Indice de acesso invalido.");
    }
    return dados[i];
}

void ListaTrechoPtr::limpa(bool deletaPonteiros) {
    if (deletaPonteiros) {
        for (int i = 0; i < tamanho; ++i) {
            delete dados[i];
        }
    }
    tamanho = 0;
}

// ===================================================================
// --- Implementação da ListaEventoPtr ---
// (Lógica idêntica, mas para Evento**)
// ===================================================================

ListaEventoPtr::ListaEventoPtr() : ListaBase() {
    dados = new Evento*[capacidade];
}

ListaEventoPtr::~ListaEventoPtr() {
    delete[] dados;
}

void ListaEventoPtr::redimensiona() {
    capacidade *= 2;
    Evento** novosDados = new Evento*[capacidade];
    for (int i = 0; i < tamanho; ++i) {
        novosDados[i] = dados[i];
    }
    delete[] dados;
    dados = novosDados;
}

void ListaEventoPtr::insere(Evento* item) {
    if (tamanho == capacidade) {
        redimensiona();
    }
    dados[tamanho] = item;
    tamanho++;
}

/**
 * [ROBUSTO] Acessa o item no índice 'i' com verificação de limites.
 */
Evento* ListaEventoPtr::get(int i) {
    if (i < 0 || i >= tamanho) {
        throw std::runtime_error("Erro [ListaEventoPtr]: Indice de acesso invalido.");
    }
    return dados[i];
}

/**
 * [ROBUSTO] Define o item no índice 'i' com verificação de limites.
 */
void ListaEventoPtr::set(int i, Evento* item) {
    // Usado pelo MinHeap (heapify e troca), precisa ser robusto
    if (i < 0 || i >= tamanho) {
        throw std::runtime_error("Erro [ListaEventoPtr]: Indice de SET invalido.");
    }
    dados[i] = item;
}

void ListaEventoPtr::removeUltimo() {
    if (tamanho > 0) {
        tamanho--;
    }
}

void ListaEventoPtr::limpa(bool deletaPonteiros) {
    if (deletaPonteiros) {
        for (int i = 0; i < tamanho; ++i) {
            delete dados[i];
        }
    }
    tamanho = 0;
}

// ===================================================================
// --- Implementação da ListaCorridaPtr ---
// (Lógica idêntica, mas para Corrida**)
// ===================================================================

ListaCorridaPtr::ListaCorridaPtr() : ListaBase() {
    dados = new Corrida*[capacidade];
}

ListaCorridaPtr::~ListaCorridaPtr() {
    delete[] dados;
}

void ListaCorridaPtr::redimensiona() {
    capacidade *= 2;
    Corrida** novosDados = new Corrida*[capacidade];
    for (int i = 0; i < tamanho; ++i) {
        novosDados[i] = dados[i];
    }
    delete[] dados;
    dados = novosDados;
}

void ListaCorridaPtr::insere(Corrida* item) {
    if (tamanho == capacidade) {
        redimensiona();
    }
    dados[tamanho] = item;
    tamanho++;
}

/**
 * [ROBUSTO] Acessa o item no índice 'i' com verificação de limites.
 */
Corrida* ListaCorridaPtr::get(int i) {
    if (i < 0 || i >= tamanho) {
        throw std::runtime_error("Erro [ListaCorridaPtr]: Indice de acesso invalido.");
    }
    return dados[i];
}

void ListaCorridaPtr::limpa(bool deletaPonteiros) {
    if (deletaPonteiros) {
        for (int i = 0; i < tamanho; ++i) {
            delete dados[i];
        }
    }
    tamanho = 0;
}

// ===================================================================
// --- Implementação da Corrida ---
// ===================================================================

Corrida::Corrida() {
    // Construtor inicializa as variáveis
    distanciaTotal = 0.0;
    somaDistIndividual = 0.0;
    // As listas internas (idsDemandas, paradas, trechos)
    // são inicializadas automaticamente por seus próprios construtores.
}

Corrida::~Corrida() {
    // O destrutor chama 'limpa' para liberar a memória
    // alocada para as paradas e trechos.
    limpa();
}

// Libera a memória de todos os ponteiros (Parada* e Trecho*)
// armazenados nas listas internas.
void Corrida::limpa() {
    idsDemandas.limpa();
    // 'true' = deleta os ponteiros de Parada/Trecho
    paradas.limpa(true); 
    trechos.limpa(true);
    distanciaTotal = 0.0;
    somaDistIndividual = 0.0;
}

// ===================================================================
// --- Implementação do MinHeap ---
// ===================================================================

MinHeap::MinHeap() {
    // O construtor da 'ListaEventoPtr heap' já é chamado
}

MinHeap::~MinHeap() {
    // O destrutor 'finaliza' é chamado para limpar a memória
    finaliza();
}

// Funções auxiliares para navegação no array (base 0)
int MinHeap::pai(int i) { return (i - 1) / 2; }
int MinHeap::esq(int i) { return 2 * i + 1; }
int MinHeap::dir(int i) { return 2 * i + 2; }

// Troca dois eventos de posição no array base
void MinHeap::troca(int i, int j) {
    Evento* temp = heap.get(i);
    heap.set(i, heap.get(j));
    heap.set(j, temp);
}

// Corrige o heap "subindo" (bubble-up)
void MinHeap::heapifyUp(int i) {
    // Enquanto o nó 'i' não for a raiz E for menor que seu pai
    while (i > 0 && heap.get(i)->tempo < heap.get(pai(i))->tempo) {
        troca(i, pai(i)); // Troca com o pai
        i = pai(i);       // Continua subindo
    }
}

// Corrige o heap "descendo" (bubble-down)
void MinHeap::heapifyDown(int i) {
    int e = esq(i);
    int d = dir(i);
    int menor = i; // Assume que 'i' (pai) é o menor

    // Se o filho da esquerda existir e for menor que o pai
    if (e < heap.getTamanho() && heap.get(e)->tempo < heap.get(menor)->tempo) {
        menor = e;
    }
    // Se o filho da direita existir e for menor que o (pai OU filho da esq)
    if (d < heap.getTamanho() && heap.get(d)->tempo < heap.get(menor)->tempo) {
        menor = d;
    }

    // Se o menor não for mais o pai, troca e continua descendo
    if (menor != i) {
        troca(i, menor);
        heapifyDown(menor); // Chamada recursiva
    }
}

// Insere um novo evento no heap
void MinHeap::insere(Evento* e) {
    heap.insere(e); // Adiciona no final da lista
    heapifyUp(heap.getTamanho() - 1); // Corrige subindo
}

// Remove e retorna o evento com o menor tempo (raiz)
Evento* MinHeap::retiraProximo() {
    // Programação defensiva: se o heap estiver vazio, retorna nulo
    if (estaVazio()) {
        return nullptr;
    }

    Evento* e = heap.get(0); // Pega a raiz (menor tempo)

    // Substitui a raiz pelo último elemento
    heap.set(0, heap.get(heap.getTamanho() - 1));
    heap.removeUltimo(); // Remove o último

    // Corrige o heap "descendo" a partir da nova raiz (índice 0)
    if (!estaVazio()) {
        heapifyDown(0);
    }

    return e; // Retorna o evento que estava na raiz
}

bool MinHeap::estaVazio() {
    return heap.estaVazia();
}

// Libera a memória de todos os Eventos* que ainda estão no heap
void MinHeap::finaliza() {
    // 'true' = deleta os ponteiros de Evento
    heap.limpa(true);
}

// ===================================================================
// --- Implementação do Simulador ---
// ===================================================================

Simulador::Simulador() {
    relogio = 0.0;
    // Parâmetros são inicializados no main.cpp
}

Simulador::~Simulador() {
    // Libera a memória de todas as demandas e corridas
    demandas.limpa(true);
    corridas.limpa(true);
}

/**
 * Fase 1: Agrupamento de Corridas.
 * Itera por todas as demandas (c0) e tenta adicionar demandas
 * subsequentes (ci) a ela.
 */
void Simulador::combinarCorridas() {
    // Loop externo (c0): Itera por cada demanda na lista mestra
    for (int i = 0; i < demandas.getTamanho(); ++i) {
        Demanda* c0 = demandas.get(i);

        // Se a demanda c0 já foi atendida (estado != 0), pula para a próxima
        if (c0->estado != 0) {
            continue;
        }

        // Cria uma nova corrida
        Corrida* proposta = new Corrida();
        
        // Adiciona c0 à proposta e atualiza seu estado
        proposta->idsDemandas.insere(c0->id);
        c0->estado = 1; // 1 = agrupada

        // Loop interno (ci): Tenta adicionar demandas subsequentes
        for (int j = i + 1; j < demandas.getTamanho(); ++j) {
            Demanda* ci = demandas.get(j);

            // 1. Verifica [DELTA] (janela de tempo)
            // Se 'ci' está fora da janela de tempo de 'c0'
            if (ci->tempo > c0->tempo + delta) {
                // ASSUMINDO QUE AS DEMANDAS ESTÃO ORDENADAS POR TEMPO:
                // Se esta 'ci' está fora, todas as próximas também estarão.
                // Isso otimiza o loop, parando a busca mais cedo.
                break; 
            }

            // 2. Verifica se ci está livre (estado == 0)
            if (ci->estado != 0) {
                continue; // Pula para a próxima 'ci'
            }

            // 3. Verifica [ETA] (capacidade do veículo)
            if (proposta->idsDemandas.getTamanho() == eta) {
                // Se a corrida está cheia, para de adicionar
                break;
            }

            // 4. Verifica [ALFA, BETA, LAMBDA] (validação complexa)
            // Esta função simula a adição e checa todos os critérios
            if (validarCombinacao(proposta, ci)) {
                // Se ci passou em todos os testes, adiciona permanentemente
                proposta->idsDemandas.insere(ci->id);
                ci->estado = 1; // 1 = agrupada
            }
        }

        // Após checar todas as 'ci', a 'proposta' está finalizada.
        // Constrói a rota final e adiciona à lista mestra de corridas.
        construirRota(proposta);
        corridas.insere(proposta);
    }
}

/**
 * Função auxiliar que valida os critérios [ALFA], [BETA] e [LAMBDA].
 * Retorna 'true' se a 'novaDemanda' (ci) pode ser adicionada à 'proposta'.
 */
bool Simulador::validarCombinacao(Corrida* proposta, Demanda* novaDemanda) {
    // 1. Verifica [ALFA] (distância de origem)
    // Compara a origem de 'ci' com a origem de *todas* as demandas (k)
    // que já estão na proposta.
    for (int k = 0; k < proposta->idsDemandas.getTamanho(); ++k) {
        int idDemandaK = proposta->idsDemandas.get(k);
        // IMPORTANTE: Esta lógica assume que o ID da demanda é o índice
        // dela na lista mestra 'demandas'. (ex: ID 0 está no índice 0)
        Demanda* demandaK = demandas.get(idDemandaK); 
        
        // Se a distância for maior que alfa, falha a validação
        if (calcularDistancia(novaDemanda->origem, demandaK->origem) > alfa) {
            return false;
        }
    }

    // 2. Verifica [BETA] (distância de destino)
    // Compara o destino de 'ci' com o destino de *todas* as demandas (k)
    for (int k = 0; k < proposta->idsDemandas.getTamanho(); ++k) {
        int idDemandaK = proposta->idsDemandas.get(k);
        Demanda* demandaK = demandas.get(idDemandaK); // Mesma premissa ID == índice

        if (calcularDistancia(novaDemanda->destino, demandaK->destino) > beta) {
            return false;
        }
    }

    // 3. Verifica [LAMBDA] (eficiência da rota)
    
    // Simula a adição da nova demanda temporariamente
    proposta->idsDemandas.insere(novaDemanda->id);
    
    // Constrói a rota *temporária* (com a nova demanda)
    // Esta função recalcula 'distanciaTotal' e 'somaDistIndividual'
    construirRota(proposta);

    // Calcula a eficiência (Lambda = Soma(Distâncias Ideais) / Distância Real da Rota)
    double eficiencia;
    if (proposta->distanciaTotal == 0) {
        // Evita divisão por zero (caso de distância 0)
        eficiencia = 1.0; 
    } else {
        eficiencia = proposta->somaDistIndividual / proposta->distanciaTotal;
    }
    
    // Remove a demanda temporária (desfaz a simulação)
    proposta->idsDemandas.removeUltimo();

    // Se a eficiência for menor que o limiar, falha a validação
    if (eficiencia < lambda) {
        return false;
    }
    
    // Se passou em Alfa, Beta e Lambda, retorna true
    return true;
}

/**
 * Constrói a rota (listas de Paradas e Trechos) para uma corrida.
 * Implementa a "versão básica": (Coleta1, Coleta2, ... Entrega1, Entrega2, ...)
 */
void Simulador::construirRota(Corrida* r) {
    // Limpa a rota antiga (paradas e trechos) antes de reconstruir
    r->limpa();

    // 1. Adiciona todas as paradas de COLETAS
    for (int i = 0; i < r->idsDemandas.getTamanho(); ++i) {
        int id = r->idsDemandas.get(i);
        Demanda* d = demandas.get(id); // Premissa: ID == índice
        r->paradas.insere(new Parada(d->origem, 0, id)); // 0 = Coleta
    }

    // 2. Adiciona todas as paradas de ENTREGAS
    for (int i = 0; i < r->idsDemandas.getTamanho(); ++i) {
        int id = r->idsDemandas.get(i);
        Demanda* d = demandas.get(id);
        r->paradas.insere(new Parada(d->destino, 1, id)); // 1 = Entrega
    }

    // 3. Calcula a soma das distâncias individuais (necessário para o Lambda)
    for (int i = 0; i < r->idsDemandas.getTamanho(); ++i) {
        int id = r->idsDemandas.get(i);
        Demanda* d = demandas.get(id);
        r->somaDistIndividual += calcularDistancia(d->origem, d->destino);
    }

    // 4. Cria os TRECHOS (caminho entre as paradas)
    r->distanciaTotal = 0.0;
    for (int i = 0; i < r->paradas.getTamanho() - 1; ++i) {
        Parada* p1 = r->paradas.get(i);
        Parada* p2 = r->paradas.get(i + 1);

        double dist = calcularDistancia(p1->coords, p2->coords);
        double tempo = dist * gama; // Tempo de viagem
        int tipo = p2->tipo; // O tipo do trecho é o tipo da *chegada* (p2)

        r->trechos.insere(new Trecho(p1, p2, dist, tempo, tipo));
        r->distanciaTotal += dist; // Acumula a distância total da rota real
    }
}

/**
 * Agenda o primeiro evento (a primeira coleta) de uma corrida
 * no escalonador (MinHeap).
 */
void Simulador::agendarPrimeiroEvento(Corrida* r) {
    // Se a corrida não tiver paradas (ex: corrida vazia), não agenda
    if (r->paradas.estaVazia()) {
        return;
    }

    // Pega a primeira demanda (c0) para saber o tempo de início
    int idDemanda0 = r->idsDemandas.get(0);
    Demanda* d0 = demandas.get(idDemanda0); // Premissa: ID == índice

    // Se a corrida só tem 1 demanda, só tem 1 trecho (Coleta -> Entrega)
    // O primeiro evento é a chegada na *segunda* parada (a entrega)
    if (r->idsDemandas.getTamanho() == 1) {
        Trecho* t0 = r->trechos.get(0); // Único trecho
        
        Evento* e = new Evento();
        e->tempo = d0->tempo + t0->tempo; // Tempo da demanda + tempo do trecho
        e->corrida = r;
        e->indiceProximaParada = 1; // Chegada na parada [1] (Entrega)

        escalonador.insere(e);
    } 
    // Se for compartilhada, o primeiro evento é a chegada na *segunda coleta*
    else if (r->trechos.getTamanho() > 0) {
        Trecho* t0 = r->trechos.get(0); // Trecho [0] (Coleta 0 -> Coleta 1)
        
        Evento* e = new Evento();
        e->tempo = d0->tempo + t0->tempo; // Tempo da demanda + tempo do primeiro trecho
        e->corrida = r;
        e->indiceProximaParada = 1; // Chegada na parada [1] (Coleta 1)

        escalonador.insere(e);
    }
}


/**
 * Fase 2: Simulação (Laço Principal).
 * Processa eventos do heap até que ele esteja vazio.
 */
void Simulador::simular() {
    // 1. Agenda o primeiro evento de todas as corridas
    //    (Isso precisa ser feito *antes* de iniciar o laço)
    for (int i = 0; i < corridas.getTamanho(); ++i) {
        agendarPrimeiroEvento(corridas.get(i));
    }
    
    // 2. Laço principal do Simulador de Eventos Discretos (SED)
    while (!escalonador.estaVazio()) {
        // Retira o evento mais próximo no tempo
        Evento* e = escalonador.retiraProximo();
        
        // Avança o relógio global para o tempo deste evento
        relogio = e->tempo;
        
        // Processa o evento (chegada na parada)
        processarEvento(e);
        
        // Libera a memória do evento que acabou de ser processado
        delete e;
    }
}

/**
 * Processa um evento (chegada a uma parada)
 */
void Simulador::processarEvento(Evento* e) {
    Corrida* r = e->corrida;
    int idxParadaAtual = e->indiceProximaParada;

    // Verifica se esta é a ÚLTIMA parada da rota
    if (idxParadaAtual == r->paradas.getTamanho() - 1) {
        // --- Caso 1: Fim da Corrida ---
        // Se for a última parada, a corrida terminou.
        // Imprime as estatísticas.
        gerarEstatisticas(r, e->tempo);

        // Marca todas as demandas desta corrida como "atendidas" (estado 4)
        for (int i = 0; i < r->idsDemandas.getTamanho(); ++i) {
            int id = r->idsDemandas.get(i);
            // Procura a demanda na lista mestra (baseado no ID)
            for (int j = 0; j < demandas.getTamanho(); ++j) {
                if (demandas.get(j)->id == id) {
                    demandas.get(j)->estado = 4;
                    break;
                }
            }
        }
    } else {
        // --- Caso 2: Corrida Continua ---
        // Se não for a última parada, agenda o próximo evento.
        
        // Pega o próximo trecho (o trecho que *começa* na parada atual)
        Trecho* proxTrecho = r->trechos.get(idxParadaAtual);

        // Cria um novo evento para a *próxima* parada
        Evento* proxE = new Evento();
        proxE->tempo = e->tempo + proxTrecho->tempo; // Tempo do evento = Tempo atual + Duração do trecho
        proxE->corrida = r;
        proxE->indiceProximaParada = idxParadaAtual + 1; // Aponta para a próxima parada

        // Insere o novo evento no escalonador
        escalonador.insere(proxE);
    }
}

/**
 * Imprime as estatísticas finais da corrida.
 */
void Simulador::gerarEstatisticas(Corrida* r, double tempoFinal) {
    std::cout << r->idsDemandas.get(0) << " " // ID da primeira demanda (c0)
              << r->idsDemandas.getTamanho() << " " // Número de passageiros
              << r->distanciaTotal << " "
              << tempoFinal << " "; // Tempo de conclusão

    // Imprime a lista de IDs de todos os passageiros
    for (int i = 0; i < r->idsDemandas.getTamanho(); i++) {
        std::cout << r->idsDemandas.get(i);
        if (i < r->idsDemandas.getTamanho() - 1) {
            std::cout << ",";
        }
    }
    std::cout << std::endl;
}