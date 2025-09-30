
#main so consegue ser compilado se temos os .os, ele depende dos outros
main: objeto.o lista.o main.o
	g++   -std=c++11 objeto.o lista.o main.o -o main

#para que .o exista temos que compilar o .cpp
objeto.o: src/objeto.cpp include/objeto.hpp
	g++ -I . -std=c++11 -c src/objeto.cpp -o objeto.o

lista.o: src/lista.cpp include/lista.hpp include/objeto.hpp
	g++ -I . -std=c++11 -c src/lista.cpp -o	lista.o		

main.o: src/main.cpp include/lista.hpp include/objeto.hpp
	g++ -I . -std=c++11 -c src/main.cpp -o main.o
	
#limpar os .o e o main
clean:
	rm -f *.o main

	 


 