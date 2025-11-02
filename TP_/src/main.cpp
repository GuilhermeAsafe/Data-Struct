#include <iostream>  // Para std::cerr, std::endl
#include <stdexcept> // Para std::exception
#include "Simulador.h" // A classe principal que faz todo o trabalho

/**
 * Ponto de entrada principal do programa TP2.
 * O executável final DEVE se chamar 'tp2.out'.
 * * Uso esperado (conforme VPL):
 * ./bin/tp2.out <arquivo_de_entrada>
 */
int main(int argc, char* argv[]) {
    
    // O programa espera 2 argumentos:
    // argv[0] = ./bin/tp2.out
    // argv[1] = <arquivo_de_entrada>
    if (argc != 2) {
        std::cerr << "Erro: Uso incorreto." << std::endl;
        std::cerr << "Uso: ./bin/tp2.out <arquivo_de_entrada>" << std::endl;
        return 1; // Retorna um código de erro
    }

    // Pega o nome do arquivo de entrada do segundo argumento
    const char* arquivoEntrada = argv[1];

    try {
        // 1. Cria o objeto principal da simulação
        Simulador simulador;

        // 2. Carrega os parâmetros e as demandas do arquivo de entrada
        //    (Preenche a listaDeTodasDemandas)
        simulador.carregarEntrada(arquivoEntrada);

        // 3. Executa a Fase 1:
        //    Processa as demandas, cria as Corridas e insere
        //    o primeiro evento de cada corrida no Escalonador.
        simulador.processarDemandas();

        // 4. Executa a Fase 2:
        //    Inicia o loop da simulação que processa os eventos
        //    do Escalonador até ele ficar vazio.
        //    A saída é impressa durante esta fase.
        simulador.executar();

    } catch (const std::exception& e) {
        // Captura qualquer erro padrão (ex: falha de alocação 'new',
        // std::out_of_range das suas listas, etc.)
        std::cerr << "Erro inesperado durante a execução: " << e.what() << std::endl;
        return 2; // Retorna um código de erro
    }

    // Se tudo ocorreu bem, retorna 0 (sucesso)
    return 0;
}