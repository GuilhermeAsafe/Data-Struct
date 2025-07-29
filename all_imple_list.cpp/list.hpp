#ifndef LIST_H
#define LIST_H

#include <iostream>


using namespace std;

struct node{

	int data;

	node *next;

};

//question: initialize tail & hean in .hpp or .cpp?

class algorthm{


	void insert_list(int value);
	void order_list();

	node *head = nullptr;
	node *tail = nullptr;


};



#endif
