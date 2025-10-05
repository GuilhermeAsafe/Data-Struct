# CORREÇÃO: Adicionado "movimento.o" à lista de dependências e ao comando de linkagem
main: objeto.o lista.o movimento.o main.o
	g++ -std=c++11 objeto.o lista.o movimento.o main.o -o main

#para que .o exista temos que compilar o .cpp
objeto.o: src/objeto.cpp include/objeto.hpp
	g++ -I . -std=c++11 -c src/objeto.cpp -o objeto.o

lista.o: src/lista.cpp include/lista.hpp include/objeto.hpp
	g++ -I . -std=c++11 -c src/lista.cpp -o lista.o     

movimento.o: src/movimento.cpp include/movimento.hpp include/lista.hpp include/objeto.hpp
	g++ -I . -std=c++11 -c src/movimento.cpp -o movimento.o

# CORREÇÃO OPCIONAL (BOA PRÁTICA): Adicionar a dependência de movimento.hpp
main.o: src/main.cpp include/lista.hpp include/objeto.hpp include/movimento.hpp
	g++ -I . -std=c++11 -c src/main.cpp -o main.o
    
#limpar os .o e o main
clean:
	rm -f *.o main