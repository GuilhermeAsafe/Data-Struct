# O alvo principal, agora incluindo a dependência de cena.o
main: objeto.o lista.o movimento.o cena.o main.o
	g++ -std=c++11 objeto.o lista.o movimento.o cena.o main.o -o main

#para que .o exista temos que compilar o .cpp
objeto.o: src/objeto.cpp include/objeto.hpp
	g++ -I . -std=c++11 -c src/objeto.cpp -o objeto.o

lista.o: src/lista.cpp include/lista.hpp include/objeto.hpp
	g++ -I . -std=c++11 -c src/lista.cpp -o lista.o     

movimento.o: src/movimento.cpp include/movimento.hpp include/lista.hpp include/objeto.hpp
	g++ -I . -std=c++11 -c src/movimento.cpp -o movimento.o

# NOVO ALVO: Regra para compilar o arquivo de cena
cena.o: src/cena.cpp include/cena.hpp include/lista.hpp include/objeto.hpp
	g++ -I . -std=c++11 -c src/cena.cpp -o cena.o

# O alvo main.o precisa da dependência de cena.hpp agora
main.o: src/main.cpp include/lista.hpp include/objeto.hpp include/movimento.hpp include/cena.hpp
	g++ -I . -std=c++11 -c src/main.cpp -o main.o
    
#limpar os .o e o main
clean:
	rm -f *.o main