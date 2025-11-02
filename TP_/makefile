# Makefile para o TP2 - Versão Explícita e Completa
# [cite_start]Compilador: g++ com C++11 [cite: 2054]
# Estrutura: src, include, obj, bin
# [cite_start]Executável: bin/tp2.out [cite: 2027]

# Alvo principal: 'all'
# Este alvo depende do executável final.
all: bin/tp2.out

# Regra de Linkagem:
# Cria o executável final 'bin/tp2.out'.
# Depende de TODOS os arquivos .o do seu projeto.
bin/tp2.out: obj/main.o obj/Simulador.o obj/Escalonador.o obj/MinHeap.o obj/Evento.o obj/Corrida.o obj/ListaDemanda.o obj/ListaTrecho.o obj/Trecho.o obj/Parada.o obj/Demanda.o
	@mkdir -p bin
	g++ obj/main.o obj/Simulador.o obj/Escalonador.o obj/MinHeap.o obj/Evento.o obj/Corrida.o obj/ListaDemanda.o obj/ListaTrecho.o obj/Trecho.o obj/Parada.o obj/Demanda.o -o bin/tp2.out

# --- Regras de Compilação ---
# Cada arquivo .cpp da sua pasta 'src/' TEM uma regra aqui.

# Regra para compilar main.cpp -> main.o
obj/main.o: src/main.cpp include/Simulador.h
	@mkdir -p obj
	g++ -std=c++11 -Wall -Iinclude -c src/main.cpp -o obj/main.o

# Regra para compilar Simulador.cpp -> Simulador.o
obj/Simulador.o: src/Simulador.cpp include/Simulador.h include/Escalonador.h include/ListaDemanda.h include/Corrida.h include/Evento.h include/Demanda.h include/Coordenada.h
	@mkdir -p obj
	g++ -std=c++11 -Wall -Iinclude -c src/Simulador.cpp -o obj/Simulador.o

# Regra para compilar Escalonador.cpp -> Escalonador.o
obj/Escalonador.o: src/Escalonador.cpp include/Escalonador.h include/MinHeap.h include/Evento.h
	@mkdir -p obj
	g++ -std=c++11 -Wall -Iinclude -c src/Escalonador.cpp -o obj/Escalonador.o

# Regra para compilar MinHeap.cpp -> MinHeap.o
obj/MinHeap.o: src/MinHeap.cpp include/MinHeap.h include/Evento.h
	@mkdir -p obj
	g++ -std=c++11 -Wall -Iinclude -c src/MinHeap.cpp -o obj/MinHeap.o

# Regra para compilar Evento.cpp -> Evento.o
obj/Evento.o: src/Evento.cpp include/Evento.h include/Corrida.h
	@mkdir -p obj
	g++ -std=c++11 -Wall -Iinclude -c src/Evento.cpp -o obj/Evento.o

# Regra para compilar Corrida.cpp -> Corrida.o
obj/Corrida.o: src/Corrida.cpp include/Corrida.h include/ListaDemanda.h include/ListaTrecho.h include/Trecho.h include/Demanda.h
	@mkdir -p obj
	g++ -std=c++11 -Wall -Iinclude -c src/Corrida.cpp -o obj/Corrida.o

# Regra para compilar ListaDemanda.cpp -> ListaDemanda.o
obj/ListaDemanda.o: src/ListaDemanda.cpp include/ListaDemanda.h include/Demanda.h
	@mkdir -p obj
	g++ -std=c++11 -Wall -Iinclude -c src/ListaDemanda.cpp -o obj/ListaDemanda.o

# Regra para compilar ListaTrecho.cpp -> ListaTrecho.o
obj/ListaTrecho.o: src/ListaTrecho.cpp include/ListaTrecho.h include/Trecho.h
	@mkdir -p obj
	g++ -std=c++11 -Wall -Iinclude -c src/ListaTrecho.cpp -o obj/ListaTrecho.o

# Regra para compilar Trecho.cpp -> Trecho.o
obj/Trecho.o: src/Trecho.cpp include/Trecho.h include/Parada.h include/Coordenada.h
	@mkdir -p obj
	g++ -std=c++11 -Wall -Iinclude -c src/Trecho.cpp -o obj/Trecho.o

# Regra para compilar Parada.cpp -> Parada.o
obj/Parada.o: src/Parada.cpp include/Parada.h include/Demanda.h include/Coordenada.h
	@mkdir -p obj
	g++ -std=c++11 -Wall -Iinclude -c src/Parada.cpp -o obj/Parada.o

# Regra para compilar Demanda.cpp -> Demanda.o
obj/Demanda.o: src/Demanda.cpp include/Demanda.h include/Coordenada.h
	@mkdir -p obj
	g++ -std=c++11 -Wall -Iinclude -c src/Demanda.cpp -o obj/Demanda.o


# --- Regra de Limpeza ---
# Remove todos os arquivos .o da pasta obj/ e o executável da pasta bin/
clean:
	rm -f obj/*.o bin/tp2.out