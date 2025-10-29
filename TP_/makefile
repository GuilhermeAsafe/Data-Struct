# O alvo principal, que agora depende da compilação de todos os objetos na pasta obj.
all: obj/objeto.o obj/lista.o obj/movimento.o obj/cena.o obj/main.o
	g++ -std=c++11 obj/objeto.o obj/lista.o obj/movimento.o obj/cena.o obj/main.o -o bin/tp1.out

# --- Regras de Compilação: Mover .o para /obj ---

obj/objeto.o: src/objeto.cpp include/objeto.hpp
	g++ -I . -std=c++11 -c src/objeto.cpp -o obj/objeto.o

obj/lista.o: src/lista.cpp include/lista.hpp include/objeto.hpp
	g++ -I . -std=c++11 -c src/lista.cpp -o obj/lista.o     

obj/movimento.o: src/movimento.cpp include/movimento.hpp include/lista.hpp include/objeto.hpp
	g++ -I . -std=c++11 -c src/movimento.cpp -o obj/movimento.o

obj/cena.o: src/cena.cpp include/cena.hpp include/lista.hpp include/objeto.hpp
	g++ -I . -std=c++11 -c src/cena.cpp -o obj/cena.o

obj/main.o: src/main.cpp include/lista.hpp include/objeto.hpp include/movimento.hpp include/cena.hpp
	g++ -I . -std=c++11 -c src/main.cpp -o obj/main.o
    
# --- Regra de Limpeza: Remove apenas os arquivos gerados (mantendo as pastas) ---
clean:
	rm -f obj/*.o bin/tp1.out