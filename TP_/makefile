# Makefile para o TP2 - Versão Explícita
#
# Alvo principal: 'all'
# Este alvo depende do executável final.
all: bin/tp2.out

# Regra de Linkagem:
# Cria o executável final 'bin/tp2.out'.
# Depende de TODOS os seus arquivos .o na pasta obj/.
#
# ADICIONE AQUI OS .o DO SIMULADOR, ESCALONADOR, ETC., QUANDO OS CRIAR
bin/tp2.out: obj/main.o obj/Demanda.o obj/Parada.o obj/Trecho.o obj/ListaDemanda.o obj/ListaTrecho.o obj/Corrida.o
	@mkdir -p bin
	g++ obj/main.o obj/Demanda.o obj/Parada.o obj/Trecho.o obj/ListaDemanda.o obj/ListaTrecho.o obj/Corrida.o -o bin/tp2.out

# --- Regras de Compilação ---
# Cada arquivo .cpp da sua pasta 'src/' DEVE ter uma regra aqui.

# Regra para compilar main.cpp -> main.o
# (Você precisará adicionar 'include/Simulador.h' aqui quando o criar)
obj/main.o: src/main.cpp
	@mkdir -p obj
	g++ -std=c++11 -Wall -Iinclude -c src/main.cpp -o obj/main.o

# Regra para compilar Demanda.cpp -> Demanda.o
obj/Demanda.o: src/Demanda.cpp include/Demanda.h include/Coordenada.h
	@mkdir -p obj
	g++ -std=c++11 -Wall -Iinclude -c src/Demanda.cpp -o obj/Demanda.o

# Regra para compilar Parada.cpp -> Parada.o
obj/Parada.o: src/Parada.cpp include/Parada.h include/Demanda.h include/Coordenada.h
	@mkdir -p obj
	g++ -std=c++11 -Wall -Iinclude -c src/Parada.cpp -o obj/Parada.o

# Regra para compilar Trecho.cpp -> Trecho.o
obj/Trecho.o: src/Trecho.cpp include/Trecho.h include/Parada.h include/Coordenada.h
	@mkdir -p obj
	g++ -std=c++11 -Wall -Iinclude -c src/Trecho.cpp -o obj/Trecho.o

# Regra para compilar ListaDemanda.cpp -> ListaDemanda.o (NOVO)
obj/ListaDemanda.o: src/ListaDemanda.cpp include/ListaDemanda.h include/Demanda.h
	@mkdir -p obj
	g++ -std=c++11 -Wall -Iinclude -c src/ListaDemanda.cpp -o obj/ListaDemanda.o

# Regra para compilar ListaTrecho.cpp -> ListaTrecho.o (NOVO)
obj/ListaTrecho.o: src/ListaTrecho.cpp include/ListaTrecho.h include/Trecho.h
	@mkdir -p obj
	g++ -std=c++11 -Wall -Iinclude -c src/ListaTrecho.cpp -o obj/ListaTrecho.o

# Regra para compilar Corrida.cpp -> Corrida.o (ATUALIZADO)
obj/Corrida.o: src/Corrida.cpp include/Corrida.h include/ListaDemanda.h include/ListaTrecho.h include/Trecho.h include/Demanda.h
	@mkdir -p obj
	g++ -std=c++11 -Wall -Iinclude -c src/Corrida.cpp -o obj/Corrida.o

# --- ADICIONE AQUI AS REGRAS PARA SEUS NOVOS ARQUIVOS ---
# Exemplo para quando você criar o Simulador:
#
# obj/Simulador.o: src/Simulador.cpp include/Simulador.h include/Demanda.h ... (outros includes)
# 	@mkdir -p obj
# 	g++ -std=c++11 -Wall -Iinclude -c src/Simulador.cpp -o obj/Simulador.o
#
# Exemplo para quando você criar o Escalonador:
#
# obj/Escalonador.o: src/Escalonador.cpp include/Escalonador.h include/MinHeap.h ... (outros includes)
# 	@mkdir -p obj
# 	g++ -std=c++11 -Wall -Iinclude -c src/Escalonador.cpp -o obj/Escalonador.o
#


# --- Regra de Limpeza ---
# Remove todos os arquivos .o da pasta obj/ e o executável da pasta bin/
clean:
	rm -f obj/*.o bin/tp2.out