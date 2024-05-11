#include <iostream>

using namespace std;

void f(const int &x, int &y){
	//x = 100;  //il const obbliga a non modificare il valore della x, dunque o non lo si modifica
	y = 200;	//o si elimina il const
}

void g(const int *x, int *y){
	//*x = 110;
	*y = 220;
}

int main(){
	
	//PUNTATORI
	int a = 10;
	int b = 15;
	
	int *ptr = &a;
	
	int *ptr1; //ATTENZIONE puntatore non inizializzato
	
	int *ptr2 = NULL;
	
	ptr = &b;
	
	//2. reference
	
	int &refInt = a; //si deve inizializzare
	
	cout << "refInt: "  << refInt << ", a= " << a << endl;
	
	refInt = 15;
	
	cout << "refInt: "  << refInt << ", a= " << a << endl;
	
	//passaggio per valore o per riferimeto? Sto usando i reference
	f(a, b);
	
	cout << "a: " << a << "  b: " << b << endl;
	
	g(&a, &b);
	
	cout << "a: " << a << "  b: " << b << endl;
}
