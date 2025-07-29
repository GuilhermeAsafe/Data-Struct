#include <iostream>

struct node
{

	int value;

	node* next; 
 	
};


int main(){

	node* n_1 = new node; //creating the value and ponter (necessary by linked) my head?

	node* n_2 = new node; 

	n_1 -> value = 23;

	n_1 -> next = n_2;

	n_2 -> value = 24;

	n_2 -> next = nullptr;


		std:: cout << " " << n_1 -> value << std::endl;

		std:: cout << " " << n_1 -> next -> value << std::endl;


	}

