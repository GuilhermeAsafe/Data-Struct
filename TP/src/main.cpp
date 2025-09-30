#include <iostream>

#include "include/objeto.hpp"
#include "include/lista.hpp"
 
using namespace std;


int main()
{
    listas minha_lista;

    objetos obj1('O', 1.0, 2.0, 3.0, 4.0);
    objetos obj2('O', 5.0, 6.0, 7.0, 8.0);
    objetos obj3('O', 9.0, 10.0, 11.0, 12.0);

    minha_lista.insert(obj1);
    minha_lista.insert(obj2);
    minha_lista.insert(obj3);

    minha_lista.print();

    return 0;
}