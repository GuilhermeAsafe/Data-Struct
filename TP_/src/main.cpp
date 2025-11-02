#include <iostream>
#include <stdexcept>
// #include "Simulador.h" // Você precisará criar esta classe

int main(int argc, char* argv[]) {
    // O arquivo executável DEVE se chamar tp2.out [cite: 1145]
    
    if (argc != 2) {
        std::cerr << "Erro: Uso incorreto." << std::endl;
        std::cerr << "Uso: ./bin/tp2.out <arquivo_entrada>" << std::endl;
        return 1;
    }

    const char* arquivoEntrada = argv[1];

    try {
        // --- TODO: CRIAR E USAR A CLASSE SIMULADOR ---
        // 
        // Simulador meuSimulador;
        // meuSimulador.carregarEntrada(arquivoEntrada);
        // meuSimulador.processarDemandas(); // Fase 1
        // meuSimulador.executar();          // Fase 2

        std::cout << "Arquivo de entrada: " << arquivoEntrada << std::endl;
        std::cout << "Implementação do simulador pendente." << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Erro inesperado durante a execução: " << e.what() << std::endl;
        return 2;
    }

    return 0;
}