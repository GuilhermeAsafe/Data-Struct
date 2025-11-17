import random

NUM_DEMANDAS = 10000
ARQUIVO_SAIDA = "demandas_base.txt"

# --- Limites das Coordenadas (Baseado nos seus exemplos) ---
# input_1/input_2 mostram X entre ~600-620 e Y entre ~7789-7805
X_MIN = 600.0
X_MAX = 620.0
Y_MIN = 7785.0
Y_MAX = 7805.0

# --- Configuração dos Tempos (Baseado nos seus exemplos) ---
# Os tempos são inteiros e os intervalos variam (ex: 5, 13, 15, 38...)
# Vamos simular uma nova demanda chegando entre 5 e 45s após a anterior.
MIN_INTERVALO_TEMPO = 5
MAX_INTERVALO_TEMPO = 45

print(f"Gerando {NUM_DEMANDAS} demandas para o arquivo {ARQUIVO_SAIDA}...")

tempo_atual = 0
with open(ARQUIVO_SAIDA, 'w') as f:
    for i in range(NUM_DEMANDAS): # IDs de 0 a (NUM_DEMANDAS - 1)
        
        # 1. Gerar o ID
        id_demanda = i
        
        # 2. Gerar o Tempo (começa do 0, mas a primeira demanda terá um tempo > 0)
        # O primeiro tempo é o intervalo, o segundo é o primeiro + o segundo intervalo, etc.
        intervalo_chegada = random.randint(MIN_INTERVALO_TEMPO, MAX_INTERVALO_TEMPO)
        if i == 0:
            # Garante que o primeiro tempo não seja 0, como nos exemplos
            tempo_atual = random.randint(5, 15) 
        else:
            tempo_atual += intervalo_chegada
        
        # 3. Gerar Coordenadas (com alta precisão, como nos exemplos)
        orig_x = round(random.uniform(X_MIN, X_MAX), 6)
        orig_y = round(random.uniform(Y_MIN, Y_MAX), 6)
        
        # Garante que o destino não seja idêntico à origem
        dest_x = orig_x
        dest_y = orig_y
        while (dest_x == orig_x and dest_y == orig_y):
            dest_x = round(random.uniform(X_MIN, X_MAX), 6)
            dest_y = round(random.uniform(Y_MIN, Y_MAX), 6)
            
        # 4. Escrever a linha no formato correto
        # Formato: <id> <tempo> <orig.x> <orig.y> <dest.x> <dest.y>
        linha = f"{id_demanda} {tempo_atual} {orig_x} {orig_y} {dest_x} {dest_y}\n"
        f.write(linha)

print("Geração concluída!")
print(f"IDs de 0 a {NUM_DEMANDAS - 1}.")
print(f"Coordenadas X entre {X_MIN} e {X_MAX}.")
print(f"Coordenadas Y entre {Y_MIN} e {Y_MAX}.")