#include "TADs.h"
#include "Model.h"
#include <iostream>

ListaBase::ListaBase() {
    capacidade = 2;
    tamanho = 0;
}

int ListaBase::getTamanho() {
    return tamanho;
}

bool ListaBase::estaVazia() {
    return tamanho == 0;
}

ListaInt::ListaInt() : ListaBase() {
    dados = new int[capacidade];
}

ListaInt::~ListaInt() {
    delete[] dados;
}

void ListaInt::redimensiona() {
    capacidade *= 2;
    int* novosDados = new int[capacidade];
    for (int i = 0; i < tamanho; ++i) {
        novosDados[i] = dados[i];
    }
    delete[] dados;
    dados = novosDados;
}

void ListaInt::insere(int item) {
    if (tamanho == capacidade) {
        redimensiona();
    }
    dados[tamanho] = item;
    tamanho++;
}

int ListaInt::get(int i) {
    return dados[i];
}

void ListaInt::removeUltimo() {
    if (tamanho > 0) {
        tamanho--;
    }
}

void ListaInt::limpa() {
    tamanho = 0;
}

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

Demanda* ListaDemandaPtr::get(int i) {
    return dados[i];
}

void ListaDemandaPtr::set(int i, Demanda* item) {
    if (i >= 0 && i < tamanho) {
        dados[i] = item;
    }
}

void ListaDemandaPtr::limpa(bool deletaPonteiros) {
    if (deletaPonteiros) {
        for (int i = 0; i < tamanho; ++i) {
            delete dados[i];
        }
    }
    tamanho = 0;
}

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

Parada* ListaParadaPtr::get(int i) {
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

Trecho* ListaTrechoPtr::get(int i) {
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

Evento* ListaEventoPtr::get(int i) {
    return dados[i];
}

void ListaEventoPtr::set(int i, Evento* item) {
    if (i >= 0 && i < tamanho) {
        dados[i] = item;
    }
}

// --- ESTA É A FUNÇÃO QUE FALTAVA ---
void ListaEventoPtr::removeUltimo() {
    if (tamanho > 0) {
        tamanho--;
    }
}
// -------------------------------------

void ListaEventoPtr::limpa(bool deletaPonteiros) {
    if (deletaPonteiros) {
        for (int i = 0; i < tamanho; ++i) {
            delete dados[i];
        }
    }
    tamanho = 0;
}

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

Corrida* ListaCorridaPtr::get(int i) {
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

Corrida::Corrida() {
    distanciaTotal = 0;
    somaDistIndividual = 0;
}

Corrida::~Corrida() {
    limpa();
}

void Corrida::limpa() {
    trechos.limpa(true);
    paradas.limpa(true);
    idsDemandas.limpa();
    distanciaTotal = 0;
    somaDistIndividual = 0;
}

MinHeap::MinHeap() {}

MinHeap::~MinHeap() {
    finaliza();
}

int MinHeap::pai(int i) { return (i - 1) / 2; }
int MinHeap::esq(int i) { return 2 * i + 1; }
int MinHeap::dir(int i) { return 2 * i + 2; }

void MinHeap::troca(int i, int j) {
    Evento* temp = heap.get(i);
    heap.set(i, heap.get(j));
    heap.set(j, temp);
}

void MinHeap::heapifyUp(int i) {
    while (i > 0 && heap.get(i)->tempo < heap.get(pai(i))->tempo) {
        troca(i, pai(i));
        i = pai(i);
    }
}

void MinHeap::heapifyDown(int i) {
    int menor = i;
    int l = esq(i);
    int r = dir(i);
    int tamanho = heap.getTamanho();

    if (l < tamanho && heap.get(l)->tempo < heap.get(menor)->tempo) {
        menor = l;
    }
    if (r < tamanho && heap.get(r)->tempo < heap.get(menor)->tempo) {
        menor = r;
    }
    if (menor != i) {
        troca(i, menor);
        heapifyDown(menor);
    }
}

void MinHeap::insere(Evento* e) {
    heap.insere(e);
    heapifyUp(heap.getTamanho() - 1);
}

Evento* MinHeap::retiraProximo() {
    if (heap.estaVazia()) {
        return 0;
    }
    if (heap.getTamanho() == 1) {
        Evento* e = heap.get(0);
        heap.limpa(false);
        return e;
    }

    Evento* root = heap.get(0);
    Evento* ultimo = heap.get(heap.getTamanho() - 1);
    heap.set(0, ultimo);
    
    heap.removeUltimo();
    
    heapifyDown(0);
    return root;
}

bool MinHeap::estaVazio() {
    return heap.estaVazia();
}

void MinHeap::finaliza() {
    heap.limpa(true);
}

Simulador::Simulador() {
    relogio = 0;
    eta = 0;
    gama = 1;
    delta = 0;
    alfa = 0;
    beta = 0;
    lambda = 0;
}

Simulador::~Simulador() {
    demandas.limpa(true);
    corridas.limpa(true);
}

void Simulador::run() {
    combinarCorridas();
    simular();
}

void Simulador::combinarCorridas() {
    for (int i = 0; i < demandas.getTamanho(); ++i) {
        Demanda* c0 = demandas.get(i);
        
        if (c0->estado != 1) {
            continue;
        }

        Corrida* novaCorrida = new Corrida();
        ListaInt indicesCombinados;
        
        indicesCombinados.insere(i);
        c0->estado = 3;

        construirRota(novaCorrida, indicesCombinados);

        for (int j = i + 1; j < demandas.getTamanho(); ++j) {
            if (indicesCombinados.getTamanho() >= eta) {
                break;
            }

            Demanda* ci = demandas.get(j);

            if (ci->estado != 1) {
                continue;
            }

            if (ci->tempo - c0->tempo >= delta) {
                continue;
            }

            bool criterioOK = true;
            for (int k = 0; k < indicesCombinados.getTamanho(); ++k) {
                Demanda* ck = demandas.get(indicesCombinados.get(k));
                
                if (calcularDistancia(ci->origem, ck->origem) > alfa) {
                    criterioOK = false;
                    break;
                }
                if (calcularDistancia(ci->destino, ck->destino) > beta) {
                    criterioOK = false;
                    break;
                }
            }

            if (!criterioOK) {
                continue;
            }

            indicesCombinados.insere(j);
            construirRota(novaCorrida, indicesCombinados);

            double eficiencia = (novaCorrida->distanciaTotal > 0)
                                ? (novaCorrida->somaDistIndividual / novaCorrida->distanciaTotal)
                                : 1.0;

            if (eficiencia < lambda) {
                indicesCombinados.removeUltimo();
                construirRota(novaCorrida, indicesCombinados);
                break;
            } else {
                ci->estado = 3;
            }
        }

        corridas.insere(novaCorrida);

        Evento* e = new Evento();
        e->tempo = c0->tempo;
        e->corrida = novaCorrida;
        e->indiceProximaParada = 0;

        processarEvento(e);
        delete e;
    }
}

void Simulador::construirRota(Corrida* r, ListaInt& indicesDemandas) {
    r->limpa();
    
    int n = indicesDemandas.getTamanho();

    for (int i = 0; i < n; ++i) {
        Demanda* d = demandas.get(indicesDemandas.get(i));
        r->idsDemandas.insere(d->id);
        r->somaDistIndividual += calcularDistancia(d->origem, d->destino);
        r->paradas.insere(new Parada(d->origem, 0, d->id));
    }

    for (int i = 0; i < n; ++i) {
        Demanda* d = demandas.get(indicesDemandas.get(i));
        r->paradas.insere(new Parada(d->destino, 1, d->id));
    }

    r->distanciaTotal = 0;
    for (int i = 0; i < r->paradas.getTamanho() - 1; ++i) {
        Parada* p1 = r->paradas.get(i);
        Parada* p2 = r->paradas.get(i+1);

        double dist = calcularDistancia(p1->coords, p2->coords);
        double tempo = dist / gama;
        
        int tipo = 2;
        if (p1->tipo == 0 && p2->tipo == 0) tipo = 0;
        if (p1->tipo == 1 && p2->tipo == 1) tipo = 1;

        r->trechos.insere(new Trecho(p1, p2, dist, tempo, tipo));
        r->distanciaTotal += dist;
    }
}

void Simulador::simular() {
    while (!escalonador.estaVazio()) {
        Evento* e = escalonador.retiraProximo();
        relogio = e->tempo;
        processarEvento(e);
        delete e;
    }
}

void Simulador::processarEvento(Evento* e) {
    Corrida* r = e->corrida;
    int idxParadaAtual = e->indiceProximaParada;

    if (idxParadaAtual == r->paradas.getTamanho() - 1) {
        gerarEstatisticas(r, e->tempo);
        
        for(int i=0; i < r->idsDemandas.getTamanho(); ++i) {
            int id = r->idsDemandas.get(i);
            for(int j=0; j < demandas.getTamanho(); ++j) {
                if(demandas.get(j)->id == id) {
                    demandas.get(j)->estado = 4;
                    break;
                }
            }
        }
    } else {
        Trecho* proxTrecho = r->trechos.get(idxParadaAtual);
        
        Evento* proxE = new Evento();
        proxE->tempo = e->tempo + proxTrecho->tempo;
        proxE->corrida = r;
        proxE->indiceProximaParada = idxParadaAtual + 1;
        
        escalonador.insere(proxE);
    }
}

void Simulador::gerarEstatisticas(Corrida* r, double tempoConclusao) {
    std::cout << tempoConclusao << " "
              << r->distanciaTotal << " "
              << r->paradas.getTamanho();

    for (int i = 0; i < r->paradas.getTamanho(); ++i) {
        Parada* p = r->paradas.get(i);
        std::cout << " " << p->coords.x << " " << p->coords.y;
    }
    std::cout << std::endl;
}