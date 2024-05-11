#include <iostream>
using namespace std;

// Esempi di costruttori
class NoConstruct{
	public:
		float f;
		char c;
		int i;
		void printAll() const{
			cout << f << " " << c << " " << i << endl;
		}
};

class A{
	public:
		int uno = 1;
		void printAll() const{
			cout << endl << "Dati membro:" << endl;
			cout << uno << endl;
			cout << due << endl;
			cout << tre << endl;
		}
		A();
		A(int,int);
		A(int,int,int);
		setDataMember(int memb, int val);
		
	private:
		int due;
		int const tre = 6; // deve essere inizializzata alla creazione
};

A::A(){}
A::A(int x1, int x2, int x3):tre(x3){
	uno = x1;
	due = x2;	
}
A::A(int x1, int x2){
	uno = x1;
	due = x2;
}


A::setDataMember(int memb, int val){
	switch(memb){
		case 1: uno = val; break;
		case 2: due = val; break;
		//case 3: tre = val; break;  è const quindi non modificabile
	}
}

int main(){
	NoConstruct noc1{4.5};
	NoConstruct noc2{4.5,'S'};
	NoConstruct noc3{4.5,'S',10};
	//Errore di compilazione per NoConstruct noc4{'X',2,2.0};
	noc3.printAll();
	
	A obj_a;
	obj_a.printAll();
	
	obj_a.uno = 11;
	//due e tre non si possono modificare dall'esterno
	//obj_a.due = 22;
	//obj_a.tre = 13;
	
	obj_a.setDataMember(2,22);
	obj_a.printAll();
	
	A obj_b(101,102,103);
	obj_b.printAll();
	A obj_c(5,5);
	obj_c.printAll();
	
	// ripasso
	A a(1,2,3); // oggetto ordinario (istanza di una classe)
	a.printAll();
	A* ptA = &a; // puntatore ad oggetto
	ptA->printAll();
	
	A& rA = a;
	rA.setDataMember(1,100);
	rA.printAll();
	
	A* ptrA = new A(100,200,300);
	ptrA->printAll();
	delete ptrA;
	
	// array d oggetti di tipo A
	A arrA[2];
	for(int i=0; i<2; i++){
		cout << "arrA[" << i << "]:";
		arrA[i].printAll();
		cout << endl;
	}
	
	A arrA2[2] = {A(10,20,30), A(2,2)};
	for(int i=0; i<2; i++){
		cout << "arrA2[" << i << "]:";
		arrA2[i].printAll();
		cout << endl;
	}
	
	A* ptrArr3 = new A[2]; // costr. di default
	ptrArr3[0].printAll();
	
	A* ptrArr4 = new A[2] {A(30,40,50), A(1,1)};
	ptrArr4->printAll(); // è un puntatore, quindi si può accedere al primo elemento così
	(ptrArr4+1)->printAll();
	
	delete [] ptrArr3;
	delete [] ptrArr4;
	
	return 0;
}
