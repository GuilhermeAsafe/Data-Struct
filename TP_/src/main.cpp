#include <iostream>  // Para std::cerr, std::endl, std::fixed
#include <iomanip>   // Para std::setprecision
#include <stdexcept> // Para std::exception
#include "Simulador.h" // A classe principal

/**
 * Ponto de entrada principal do programa TP2.
 * Uso esperado: ./bin/tp2.out <arquivo_de_entrada>
 */
int main(int argc, char* argv[]) {
    
    // Verifica se o argumento do arquivo de entrada foi fornecido
    if (argc != 2) {
        std::cerr << "Erro: Uso incorreto." << std::endl;
        std::cerr << "Uso: ./bin/tp2.out <arquivo_de_entrada>" << std::endl;
        return 1; // Retorna um código de erro
    }

    const char* arquivoEntrada = argv[1];

    try {
        // 1. Cria o simulador
        Simulador simulador;

        // 2. Carrega os dados de entrada
        simulador.carregarEntrada(arquivoEntrada);

        // 3. Executa a Fase 1 (Agrupamento)
        simulador.processarDemandas();

        // 4. Executa a Fase 2 (Simulação)
        simulador.executar();

    } catch (const std::exception& e) {
        // Captura qualquer erro (ex: std::out_of_range, falha de 'new')
        std::cerr << "Erro inesperado durante a execução: " << e.what() << std::endl;
        return 2; // Retorna um código de erro
    }

    // 5. Sucesso
    // O destrutor do ~Simulador é chamado aqui, limpando toda a memória.
    return 0;
}