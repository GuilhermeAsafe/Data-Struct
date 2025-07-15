#include <iostream>

int i = 0;


struct node{

	int data;

	node* next;

};


int main(){

	node* head = nullptr; //i don't creating data, because head points by element the list

	node*  tail = nullptr;

	head = tail;


	while(i <= 10){

		node *n = new node;

		n -> next = nullptr;

		n -> data = i;


		if(head == nullptr){

			tail = n;

			head = n; 

		}

		 tail-> next = n;

		 tail = n;

		i++;


	}

	node* n = head; //its ok? faz sentido?? 

	while(n != nullptr){

		std::cout << " " << n -> data << std::endl;

		n = n -> next;

	}

}