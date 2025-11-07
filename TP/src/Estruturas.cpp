#include "Estruturas.h"

// --- Coordenada.cpp ---
Coordenada::Coordenada(double x_val, double y_val) : x(x_val), y(y_val) {}

double Coordenada::distancia(const Coordenada& outra) const {
    return std::sqrt(std::pow(this->x - outra.x, 2) + std::pow(this->y - outra.y, 2));
}

// --- Demanda.cpp ---
Demanda::Demanda(int id, int tempo, Coordenada origem, Coordenada destino)
    : id(id), 
      tempo(tempo), 
      origem(origem), 
      destino(destino), 
      estado(DEMANDADA) 
{}

double Demanda::getDistanciaIdeal() const {
    return this->origem.distancia(this->destino);
}

// --- Parada.cpp ---
Parada::Parada()
    : localizacao(0.0, 0.0), tipo(EMBARQUE), passageiro(nullptr) 
{}

Parada::Parada(Coordenada loc, TipoParada tipo, Demanda* passageiro)
    : localizacao(loc), tipo(tipo), passageiro(passageiro) 
{}

// --- Trecho.cpp ---
Trecho::Trecho()
    : paradaOrigem(nullptr), paradaDestino(nullptr), 
      distancia(0.0), tempoGasto(0.0), natureza(DESLOCAMENTO) 
{}

Trecho::Trecho(Parada* origem, Parada* destino, double gama_velocidade)
    : paradaOrigem(origem), paradaDestino(destino) 
{
    if (origem == nullptr || destino == nullptr) {
        distancia = 0.0;
        tempoGasto = 0.0;
    } else {
        distancia = origem->localizacao.distancia(destino->localizacao);
    }
    
    if (gama_velocidade == 0.0) {
        tempoGasto = 0.0;
    } else {
        tempoGasto = distancia / gama_velocidade;
    }
    
    definirNatureza();
}

void Trecho::definirNatureza() {
    if (paradaOrigem == nullptr || paradaDestino == nullptr) {
        natureza = DESLOCAMENTO;
        return;
    }

    if (paradaOrigem->tipo == EMBARQUE && paradaDestino->tipo == EMBARQUE) {
        natureza = COLETA;
    } else if (paradaOrigem->tipo == DESEMBARQUE && paradaDestino->tipo == DESEMBARQUE) {
        natureza = ENTREGA;
    } else {
        natureza = DESLOCAMENTO;
    }
}

// --- Evento.cpp ---
Evento::Evento(double t, TipoEvento tp, Corrida* c, int indice)
    : tempo(t), tipo(tp), corrida(c), indiceTrecho(indice) 
{}

bool Evento::operator>(const Evento& outro) const {
    return this->tempo > outro.tempo;
}

// --- ListaDemanda.cpp ---
NoDemanda::NoDemanda(Demanda* d) : dado(d), proximo(nullptr) {}
ListaDemanda::ListaDemanda() : inicio(nullptr), fim(nullptr), tamanho(0) {}
ListaDemanda::~ListaDemanda() { clear(); }

void ListaDemanda::push_back(Demanda* d) {
    NoDemanda* novoNo = new NoDemanda(d);
    if (empty()) {
        inicio = novoNo;
        fim = novoNo;
    } else {
        fim->proximo = novoNo;
        fim = novoNo;
    }
    tamanho++;
}
Demanda* ListaDemanda::get(int index) {
    if (index < 0 || index >= tamanho) {
        throw std::out_of_range("Índice fora dos limites da ListaDemanda");
    }
    NoDemanda* atual = inicio;
    for (int i = 0; i < index; ++i) {
        atual = atual->proximo;
    }
    return atual->dado;
}
Demanda* ListaDemanda::pop_back() {
    if (empty()) {
        throw std::out_of_range("pop_back() em ListaDemanda vazia");
    }
    Demanda* dadoRemovido = fim->dado;
    if (tamanho == 1) {
        delete inicio;
        inicio = nullptr;
        fim = nullptr;
    } else {
        NoDemanda* atual = inicio;
        while (atual->proximo != fim) {
            atual = atual->proximo;
        }
        delete fim;
        fim = atual;
        fim->proximo = nullptr;
    }
    tamanho--;
    return dadoRemovido;
}
int ListaDemanda::size() const { return tamanho; }
bool ListaDemanda::empty() const { return tamanho == 0; }
void ListaDemanda::clear() {
    NoDemanda* atual = inicio;
    while (atual != nullptr) {
        NoDemanda* proximo = atual->proximo;
        delete atual; 
        atual = proximo;
    }
    inicio = nullptr;
    fim = nullptr;
    tamanho = 0;
}

// --- ListaParada.cpp ---
NoParada::NoParada(Parada p) : dado(p), proximo(nullptr) {}
ListaParada::ListaParada() : inicio(nullptr), fim(nullptr), tamanho(0) {}
ListaParada::~ListaParada() { clear(); }

void ListaParada::push_back(Parada p) {
    NoParada* novoNo = new NoParada(p);
    if (empty()) {
        inicio = novoNo;
        fim = novoNo;
    } else {
        fim->proximo = novoNo;
        fim = novoNo;
    }
    tamanho++;
}
Parada* ListaParada::get(int index) {
    if (index < 0 || index >= tamanho) {
        throw std::out_of_range("Índice fora dos limites da ListaParada");
    }
    NoParada* atual = inicio;
    for (int i = 0; i < index; ++i) {
        atual = atual->proximo;
    }
    return &(atual->dado);
}
int ListaParada::size() const { return tamanho; }
bool ListaParada::empty() const { return tamanho == 0; }

void ListaParada::clear() {
    NoParada* atual = inicio;
    while (atual != nullptr) {
        // CORRIGIDO (Bug do 'NoDemanda*')
        NoParada* proximo = atual->proximo; 
        delete atual;
        atual = proximo;
    }
    inicio = nullptr;
    fim = nullptr;
    tamanho = 0;
}

// --- ListaTrecho.cpp ---
NoTrecho::NoTrecho(Trecho t) : dado(t), proximo(nullptr) {}
ListaTrecho::ListaTrecho() : inicio(nullptr), fim(nullptr), tamanho(0) {}
ListaTrecho::~ListaTrecho() { clear(); }

void ListaTrecho::push_back(Trecho t) {
    NoTrecho* novoNo = new NoTrecho(t);
    if (empty()) {
        inicio = novoNo;
        fim = novoNo;
    } else {
        fim->proximo = novoNo;
        fim = novoNo;
    }
    tamanho++;
}
Trecho& ListaTrecho::get(int index) {
    if (index < 0 || index >= tamanho) {
        throw std::out_of_range("Índice fora dos limites da ListaTrecho");
    }
    NoTrecho* atual = inicio;
    for (int i = 0; i < index; ++i) {
        atual = atual->proximo;
    }
    return atual->dado;
}
int ListaTrecho::size() const { return tamanho; }
bool ListaTrecho::empty() const { return tamanho == 0; }
void ListaTrecho::clear() {
    NoTrecho* atual = inicio;
    while (atual != nullptr) {
        NoTrecho* proximo = atual->proximo;
        delete atual;
        atual = proximo;
    }
    inicio = nullptr;
    fim = nullptr;
    tamanho = 0;
}

// --- ListaCorrida.cpp ---
NoCorrida::NoCorrida(Corrida* c) : dado(c), proximo(nullptr) {}
ListaCorrida::ListaCorrida() : inicio(nullptr), fim(nullptr), tamanho(0) {}
ListaCorrida::~ListaCorrida() { clear(); }

void ListaCorrida::push_back(Corrida* c) {
    NoCorrida* novoNo = new NoCorrida(c);
    if (empty()) {
        inicio = novoNo;
        fim = novoNo;
    } else {
        fim->proximo = novoNo;
        fim = novoNo;
    }
    tamanho++;
}
Corrida* ListaCorrida::get(int index) {
    if (index < 0 || index >= tamanho) {
        throw std::out_of_range("Índice fora dos limites da ListaCorrida");
    }
    NoCorrida* atual = inicio;
    for (int i = 0; i < index; ++i) {
        atual = atual->proximo;
    }
    return atual->dado;
}
int ListaCorrida::size() const { return tamanho; }
bool ListaCorrida::empty() const { return tamanho == 0; }
void ListaCorrida::clear() {
    NoCorrida* atual = inicio;
    while (atual != nullptr) {
        NoCorrida* proximo = atual->proximo;
        delete atual;
        atual = proximo;
    }
    inicio = nullptr;
    fim = nullptr;
    tamanho = 0;
}

// --- Corrida.cpp ---
Corrida::Corrida(double gama)
    : gama_velocidade(gama),
      distanciaTotal(0.0), 
      tempoTotal(0.0), 
      eficiencia(1.0), 
      numeroParadas(0)
{}

Corrida::~Corrida() {
    demandasAtendidas.clear();
    trechos.clear();
    paradas.clear();
}

void Corrida::reconstruirRota() {
    trechos.clear();
    paradas.clear();
    distanciaTotal = 0.0;
    tempoTotal = 0.0;
    numeroParadas = 0;

    int numDemandas = demandasAtendidas.size();
    if (numDemandas == 0) {
        eficiencia = 1.0; 
        return;
    }

    for (int i = 0; i < numDemandas; ++i) {
        Demanda* d = demandasAtendidas.get(i);
        paradas.push_back(Parada(d->origem, EMBARQUE, d));
    }
    
    // --- CORREÇÃO DO VALGRIND (Bug 2) ---
    // O 'r' foi substituído por '0'
    for (int i = 0; i < numDemandas; ++i) { 
        Demanda* d = demandasAtendidas.get(i);
        paradas.push_back(Parada(d->destino, DESEMBARQUE, d));
    }
    // --- FIM DA CORREÇÃO ---

    this->numeroParadas = paradas.size();

    for (int i = 0; i < this->numeroParadas - 1; ++i) {
        Parada* pOrigem = paradas.get(i);
        Parada* pDestino = paradas.get(i + 1);
        
        Trecho novoTrecho(pOrigem, pDestino, this->gama_velocidade);
        trechos.push_back(novoTrecho);
        
        distanciaTotal += novoTrecho.distancia;
        tempoTotal += novoTrecho.tempoGasto;
    }

    calcularEficiencia();
}

void Corrida::adicionarDemanda(Demanda* demanda) {
    demandasAtendidas.push_back(demanda);
    reconstruirRota();
}

void Corrida::removerUltimaDemanda() {
    demandasAtendidas.pop_back(); 
    reconstruirRota(); 
}

void Corrida::calcularEficiencia() {
    if (demandasAtendidas.empty() || distanciaTotal == 0.0) {
        this->eficiencia = 1.0; 
        return;
    }

    double distanciaIdealSoma = 0.0;
    for (int i = 0; i < demandasAtendidas.size(); ++i) {
        distanciaIdealSoma += demandasAtendidas.get(i)->getDistanciaIdeal();
    }

    this->eficiencia = distanciaIdealSoma / this->distanciaTotal;
}

// --- MinHeap.cpp ---
MinHeap::MinHeap() : capacidade(10), tamanho(0) {
    dados = new Evento*[capacidade];
}

MinHeap::~MinHeap() {
    for (int i = 0; i < tamanho; ++i) {
        delete dados[i];
    }
    delete[] dados;
}

void MinHeap::redimensionar() {
    capacidade *= 2;
    Evento** novosDados = new Evento*[capacidade];
    for (int i = 0; i < tamanho; ++i) {
        novosDados[i] = dados[i];
    }
    delete[] dados; 
    dados = novosDados;
}

void MinHeap::swap(int i, int j) {
    Evento* temp = dados[i];
    dados[i] = dados[j];
    dados[j] = temp;
}

void MinHeap::heapifyUp(int index) {
    while (index > 0 && (*dados[index] > *dados[getParent(index)] == false)) {
        swap(index, getParent(index));
        index = getParent(index);
    }
}

void MinHeap::heapifyDown(int index) {
    int left = getLeftChild(index);
    int right = getRightChild(index);
    int menor = index;

    if (left < tamanho && (*dados[left] > *dados[menor] == false)) {
        menor = left;
    }
    if (right < tamanho && (*dados[right] > *dados[menor] == false)) {
        menor = right;
    }

    if (menor != index) {
        swap(index, menor);
        heapifyDown(menor);
    }
}

void MinHeap::inserir(Evento* evento) {
    if (tamanho == capacidade) {
        redimensionar();
    }
    dados[tamanho] = evento;
    tamanho++;
    heapifyUp(tamanho - 1);
}

Evento* MinHeap::removerMin() {
    if (estaVazio()) {
        return nullptr;
    }
    Evento* minEvento = dados[0];
    dados[0] = dados[tamanho - 1];
    tamanho--;
    
    if (tamanho > 0) {
        heapifyDown(0);
    }
    
    return minEvento;
}

bool MinHeap::estaVazio() const {
    return tamanho == 0;
}