#include <iostream>  
#include <iomanip>   
#include <stdexcept> 
// fstream e cstdio não são mais necessários
#include "Simulador.h" 

/**
 * Ponto de entrada principal do programa TP2.
 * Uso: ./bin/tp2.out < <arquivo_de_entrada>
 */
int main(){

    // Argumentos argc/argv não são mais usados
    
    try {
        Simulador simulador;

        // --- MODO CIN (TERMINAL) ---
        simulador.carregarEntrada(); // Passa o cin

        // 3. Executa a Fase 1 (Agrupamento)
        simulador.processarDemandas();

        // 4. Executa a Fase 2 (Simulação)
        simulador.executar();

    } catch (const std::exception& e) {
        std::cerr << "Erro inesperado durante a execução: " << e.what() << std::endl;
        return 2; 
    }

    // 5. Sucesso
    return 0;
}