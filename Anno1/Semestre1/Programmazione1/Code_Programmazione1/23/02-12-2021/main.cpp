#include "A.h"
#include <iostream>

int main() {
	double z = 4.5;
	//oggetti a e b allocati nello STACK
	A a = A(z);  //a è il nome che identifica il nuovo oggetto di tipo A
	A b(z);  //uguale ma con b
	//oggetto di tipo A allocato nel free store
	A* objptr = new A(z);

	a.setX(1.2);
	b.setX2(2.4);

	objptr->setX(3.4);
	(*objptr).setX2(4.5);
}