# Makefile para o TP2 - Versão Refatorada (6 arquivos)
# Compilador: g++ com C++11
# Estrutura: src, include, obj, bin
# Executável: bin/tp2.out

# Alvo principal
all: bin/tp2.out

# Regra de Linkagem
bin/tp2.out: obj/main.o obj/Simulador.o obj/Estruturas.o
	@mkdir -p bin
	g++ obj/main.o obj/Simulador.o obj/Estruturas.o -o bin/tp2.out
	@echo "Executável bin/tp2.out criado com sucesso."

# --- Regras de Compilação ---

# Regra para compilar main.cpp -> main.o
obj/main.o: src/main.cpp include/Simulador.h
	@mkdir -p obj
	g++ -std=c++11  -Iinclude -c src/main.cpp -o obj/main.o

# Regra para compilar Simulador.cpp -> Simulador.o
obj/Simulador.o: src/Simulador.cpp include/Simulador.h include/Estruturas.h
	@mkdir -p obj
	g++ -std=c++11  -Iinclude -c src/Simulador.cpp -o obj/Simulador.o

# Regra para compilar Estruturas.cpp -> Estruturas.o
obj/Estruturas.o: src/Estruturas.cpp include/Estruturas.h
	@mkdir -p obj
	g++ -std=c++11 -Iinclude -c src/Estruturas.cpp -o obj/Estruturas.o


# --- Regra de Limpeza ---
clean:
	@rm -f obj/*.o bin/tp2.out
	@echo "Arquivos compilados removidos."