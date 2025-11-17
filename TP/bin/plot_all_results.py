import pandas as pd
import matplotlib.pyplot as plt
import os
import sys

def gerar_grafico(csv_file, param_name):
    """
    Lê um arquivo CSV e gera um gráfico de 4 painéis.
    """
    print(f"Gerando gráfico para {csv_file}...")
    
    try:
        df = pd.read_csv(csv_file)
        if df.empty:
            print(f"  AVISO: Arquivo {csv_file} está vazio. Pulando.", file=sys.stderr)
            return
    except FileNotFoundError:
        print(f"  ERRO: Arquivo {csv_file} não encontrado. Pulando.", file=sys.stderr)
        return

    df = df.set_index(param_name)
    
    fig, axes = plt.subplots(nrows=2, ncols=2, figsize=(14, 10))
    fig.suptitle(f'Análise de Impacto do Parâmetro "{param_name.upper()}"', fontsize=16, y=1.02)

    colunas_necessarias = ['tempo_execucao_s', 'total_corridas', 'media_passageiros_por_corrida', 'distancia_total']
    for col in colunas_necessarias:
        if col not in df.columns:
            print(f"  ERRO: Coluna '{col}' não encontrada em {csv_file}.", file=sys.stderr)
            plt.close(fig)
            return

    # Gráfico 1: Tempo de Execução
    df['tempo_execucao_s'].plot(
        ax=axes[0, 0], title='Tempo de Execução (Custo Computacional)',
        marker='o', grid=True, color='red'
    )
    axes[0, 0].set_ylabel('Tempo (segundos)')
    axes[0, 0].set_xlabel(param_name)

    # Gráfico 2: Total de Corridas
    df['total_corridas'].plot(
        ax=axes[0, 1], title='Total de Corridas Geradas (Eficiência)',
        marker='o', grid=True, color='blue'
    )
    axes[0, 1].set_ylabel('Nº de Corridas')
    axes[0, 1].set_xlabel(param_name)

    # Gráfico 3: Média de Passageiros
    df['media_passageiros_por_corrida'].plot(
        ax=axes[1, 0], title='Média de Passageiros por Corrida',
        marker='o', grid=True, color='green'
    )
    axes[1, 0].set_ylabel('Passageiros / Corrida')
    axes[1, 0].set_xlabel(param_name)

    # Gráfico 4: Distância Total
    df['distancia_total'].plot(
        ax=axes[1, 1], title='Distância Total Percorrida (Custo Operacional)',
        marker='o', grid=True, color='purple'
    )
    axes[1, 1].set_ylabel('Distância (unidades)')
    axes[1, 1].set_xlabel(param_name)

    plt.tight_layout(rect=[0, 0.03, 1, 0.95])
    
    grafico_output = f"grafico_analise_{param_name}.png"
    plt.savefig(grafico_output)
    print(f"  Gráfico salvo em: {grafico_output}\n")
    plt.close(fig)

def main():
    lista_experimentos = [
        ("resultados_analise_delta.csv", "delta"),
        ("resultados_analise_alfa.csv", "alfa"),
        ("resultados_analise_beta.csv", "beta"),
        ("resultados_analise_eta.csv", "eta"),
        ("resultados_analise_lambda.csv", "lambda")
    ]
    
    print("Iniciando geração de gráficos para a Análise Experimental...")
    
    for csv_file, param_name in lista_experimentos:
        gerar_grafico(csv_file, param_name)
        
    print("Processo de plotagem concluído!")

if __name__ == "__main__":
    main()