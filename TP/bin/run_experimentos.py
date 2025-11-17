import os
import subprocess
import time
import pandas as pd
import sys

# --- Configurações Globais ---
# ATENÇÃO: Verifique o nome do seu executável!
# O PDF pede 'tp3.out', mas seu Makefile gera 'tp2.out'.
# Mude a linha abaixo para o nome correto.
EXECUTAVEL = "./tp2.out"       
ARQUIVO_DEMANDAS = "demandas_base.txt"
NUM_DEMANDAS = 10000

# --- Funções Auxiliares ---

def analisar_output(output_file):
    """Lê o arquivo de saída e calcula as métricas."""
    total_corridas = 0
    dist_total = 0.0
    
    try:
        with open(output_file, 'r') as f:
            for line in f:
                if line.strip(): # Ignora linhas em branco
                    partes = line.split()
                    if len(partes) < 2:
                        print(f"  AVISO: Linha mal formatada no output: {line.strip()}")
                        continue
                    dist_total += float(partes[1])
                    total_corridas += 1
    except Exception as e:
        print(f"    ERRO ao ler output '{output_file}': {e}", file=sys.stderr)
        return 0, 0.0
        
    return total_corridas, dist_total

def executar_teste(param_nome, param_valor, config_base):
    """Cria o input, roda o C++ e coleta as métricas."""
    
    config_atual = config_base.copy()
    config_atual[param_nome] = param_valor
    
    INPUT_TEMP = "input_teste.txt"
    OUTPUT_TEMP = "output_teste.txt"
    
    # 1. Montar o arquivo de input
    try:
        with open(INPUT_TEMP, 'w') as f:
            f.write(f"{config_atual['eta']}\n")
            f.write(f"{config_atual['gama']}\n")
            f.write(f"{config_atual['delta']}\n")
            f.write(f"{config_atual['alfa']}\n")
            f.write(f"{config_atual['beta']}\n")
            f.write(f"{config_atual['lambda']}\n")
            f.write(f"{NUM_DEMANDAS}\n")
        
        os.system(f"cat {ARQUIVO_DEMANDAS} >> {INPUT_TEMP}")
    except Exception as e:
        print(f"  ERRO ao criar input: {e}", file=sys.stderr)
        return None

    # 2. Executar o programa e medir o tempoinput
    start_time = time.time()
    
    try:
        with open(INPUT_TEMP, 'r') as f_in:
            processo = subprocess.run(
                [EXECUTAVEL],
                stdin=f_in,
                stdout=open(OUTPUT_TEMP, 'w'),
                stderr=subprocess.PIPE,
                text=True,
                timeout=300 # Timeout de 5 minutos (previne loops)
            )
    except Exception as e:
        print(f"  ERRO ao executar '{EXECUTAVEL}': {e}", file=sys.stderr)
        return None
        
    end_time = time.time()
    tempo_execucao = end_time - start_time

    if processo.stderr:
        print(f"  AVISO (stderr): {processo.stderr.strip()}")

    # 3. Coletar métricas
    total_corridas, dist_total = analisar_output(OUTPUT_TEMP)
    
    if total_corridas > 0:
        media_passageiros = NUM_DEMANDAS / total_corridas
    else:
        media_passageiros = 0

    os.remove(INPUT_TEMP)
    os.remove(OUTPUT_TEMP)

    # 4. Retornar resultados
    return {
        "tempo_execucao_s": tempo_execucao,
        "total_corridas": total_corridas,
        "media_passageiros_por_corrida": media_passageiros,
        "distancia_total": dist_total
    }

# --- Função Principal ---

def main():
    if not os.path.exists(EXECUTAVEL):
        print(f"ERRO: Executável {EXECUTAVEL} não encontrado.", file=sys.stderr)
        print("Verifique seu Makefile ou o nome do executável no script.", file=sys.stderr)
        return
    if not os.path.exists(ARQUIVO_DEMANDAS):
        print(f"ERRO: {ARQUIVO_DEMANDAS} não encontrado.", file=sys.stderr)
        print("Rode 'gerar_demandas.py' primeiro.", file=sys.stderr)
        return

    # Configuração Base Padrão
    config_padrao = {
        'eta': 4,
        'gama': 1.0,
        'delta': 500,
        'alfa': 1.0,
        'beta': 1.0,
        'lambda': 0.80
    }
    
    # Configuração Relaxada (para o teste do Lambda)
    config_relaxada = {
        'eta': 4,
        'gama': 1.0,
        'delta': 1000,
        'alfa': 2.0,
        'beta': 2.0,
        'lambda': 0.80 # Este será variado
    }

    # --- Definição de todos os 5 experimentos ---
    experimentos = [
        ("delta", [50, 100, 250, 500, 750, 1000, 1500], config_padrao),
        ("alfa", [0.25, 0.5, 1.0, 1.5, 2.0, 3.0, 5.0], config_padrao),
        ("beta", [0.25, 0.5, 1.0, 1.5, 2.0, 3.0, 5.0], config_padrao),
        ("eta", [2, 3, 4, 5, 6, 8, 10], config_padrao),
        ("lambda", [0.5, 0.6, 0.7, 0.8, 0.85, 0.9, 0.95], config_relaxada)
    ]

    for param_nome, valores, config_base in experimentos:
        
        print(f"\n--- Iniciando Análise: Variando '{param_nome.upper()}' ---")
        lista_resultados = []
        
        for valor in valores:
            print(f"  Testando {param_nome.upper()} = {valor}...")
            resultado = executar_teste(param_nome, valor, config_base)
            
            if resultado:
                resultado[param_nome] = valor # Adiciona o valor do parâmetro
                lista_resultados.append(resultado)
                print(f"    Tempo: {resultado['tempo_execucao_s']:.2f}s, Corridas: {resultado['total_corridas']}")

        # Salvar o CSV
        arquivo_csv = f"resultados_analise_{param_nome}.csv"
        df = pd.DataFrame(lista_resultados)
        df.to_csv(arquivo_csv, index=False)
        print(f"--- Relatório salvo em: {arquivo_csv} ---")
        print(df.to_string()) # Imprime a tabela no console

    print("\nTodos os experimentos foram concluídos!")

if __name__ == "__main__":
    main()