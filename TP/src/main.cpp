#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept> // Para std::exception (Robustez)
#include <new>       // Para std::bad_alloc (Robustez)

#include "TADs.h"
#include "Model.h"

int main() {
    
    // --- Bloco de Robustez (try-catch) ---
    // Tenta executar todo o programa. Se ocorrer um erro catastrófico
    // (como falta de memória ou acesso a índice inválido),
    // o bloco 'catch' irá capturá-lo e impedir o "crash".
    try {
        // Configura a precisão da saída padrão (2 casas decimais)
        std::cout.precision(2);
        std::cout << std::fixed;

        Simulador sim;
        std::string linha; // Variável para ler linhas da entrada
        int numdemandas;

        // --- 1. Leitura dos Parâmetros (Robusta, Sem Templates) ---
        // Cada parâmetro é lido linha a linha e validado.
        
        // Lê eta
        if (!std::getline(std::cin, linha)) {
            std::cerr << "Erro: Fim de arquivo inesperado ao ler 'eta'." << std::endl; return 1;
        }
        std::stringstream ss_eta(linha);
        if (!(ss_eta >> sim.eta) || !ss_eta.eof()) {
            std::cerr << "Erro: Formato invalido para o parametro 'eta'." << std::endl; return 1;
        }

        // Lê gama
        if (!std::getline(std::cin, linha)) {
             std::cerr << "Erro: Fim de arquivo inesperado ao ler 'gama'." << std::endl; return 1;
        }
        std::stringstream ss_gama(linha);
        if (!(ss_gama >> sim.gama) || !ss_gama.eof()) {
            std::cerr << "Erro: Formato invalido para o parametro 'gama'." << std::endl; return 1;
        }

        // Lê delta
        if (!std::getline(std::cin, linha)) {
             std::cerr << "Erro: Fim de arquivo inesperado ao ler 'delta'." << std::endl; return 1;
        }
        std::stringstream ss_delta(linha);
        if (!(ss_delta >> sim.delta) || !ss_delta.eof()) {
            std::cerr << "Erro: Formato invalido para o parametro 'delta'." << std::endl; return 1;
        }

        // Lê alfa
        if (!std::getline(std::cin, linha)) {
             std::cerr << "Erro: Fim de arquivo inesperado ao ler 'alfa'." << std::endl; return 1;
        }
        std::stringstream ss_alfa(linha);
        if (!(ss_alfa >> sim.alfa) || !ss_alfa.eof()) {
            std::cerr << "Erro: Formato invalido para o parametro 'alfa'." << std::endl; return 1;
        }

        // Lê beta
        if (!std::getline(std::cin, linha)) {
             std::cerr << "Erro: Fim de arquivo inesperado ao ler 'beta'." << std::endl; return 1;
        }
        std::stringstream ss_beta(linha);
        if (!(ss_beta >> sim.beta) || !ss_beta.eof()) {
            std::cerr << "Erro: Formato invalido para o parametro 'beta'." << std::endl; return 1;
        }

        // Lê lambda
        if (!std::getline(std::cin, linha)) {
             std::cerr << "Erro: Fim de arquivo inesperado ao ler 'lambda'." << std::endl; return 1;
        }
        std::stringstream ss_lambda(linha);
        if (!(ss_lambda >> sim.lambda) || !ss_lambda.eof()) {
            std::cerr << "Erro: Formato invalido para o parametro 'lambda'." << std::endl; return 1;
        }

        // Lê numdemandas
        if (!std::getline(std::cin, linha)) {
             std::cerr << "Erro: Fim de arquivo inesperado ao ler 'numdemandas'." << std::endl; return 1;
        }
        std::stringstream ss_num(linha);
        if (!(ss_num >> numdemandas) || !ss_num.eof()) {
            std::cerr << "Erro: Formato invalido para o parametro 'numdemandas'." << std::endl; return 1;
        }

        // --- 2. Leitura das Demandas (com Validação) ---
        for (int i = 0; i < numdemandas; ++i) {
            // Aloca uma nova demanda
            // (Se 'new' falhar por falta de memória, o catch(std::bad_alloc) captura)
            Demanda* d = new Demanda();

            // Tenta ler todos os 6 campos da demanda da linha
            if (!(std::cin >> d->id >> d->tempo 
                           >> d->origem.x >> d->origem.y 
                           >> d->destino.x >> d->destino.y)) 
            {
                // Se a leitura falhar (ex: formato incorreto, fim de arquivo)
                std::cerr << "Erro: Formato invalido ou dados faltantes na linha da demanda " << i << "." << std::endl;
                delete d; // Libera a demanda alocada
                return 1; // Encerra o programa
            }
            
            d->estado = 0; // Estado inicial (0 = livre)
            sim.demandas.insere(d); // Adiciona à lista mestra do simulador
        }

        // --- 3. Execução das Fases da Simulação ---

        // Fase 1: Agrupamento/Combinação de Corridas
        sim.combinarCorridas();

        // Fase 2: Simulação de Eventos Discretos (SED)
        sim.simular();

        // O destrutor do Simulador (~Simulador) será chamado automaticamente
        // no final do 'try', limpando toda a memória alocada (demandas, corridas, etc).

    } 
    // --- Bloco de Captura de Erros (Robustez) ---
    catch (const std::bad_alloc& e) {
        // [ROBUSTEZ] Captura um erro de falta de memória (ex: 'new' falhou)
        std::cerr << "ERRO CATASTROFICO: Falha de alocacao de memoria." << std::endl;
        std::cerr << "O sistema pode estar sem memoria. (" << e.what() << ")" << std::endl;
        return 2; // Encerra com código de erro de memória
    } 
    catch (const std::exception& e) {
        // [ROBUSTEZ] Captura qualquer outra exceção padrão, como:
        // - std::runtime_error (lançado pelos nossos 'get/set' robustos)
        // - Outros erros inesperados
        std::cerr << "ERRO CATASTROFICO: Uma excecao ocorreu." << std::endl;
        std::cerr << "       Detalhes: " << e.what() << std::endl;
        return 3; // Encerra com código de erro de lógica
    }

    return 0; // Sucesso
}