#include <iostream>

using namespace std;

/*Scrivere un programma che inizializza solo i primi due elementi di un vettore di 4 e
visualizzi il valore degli elementi non assegnati.*/

template <typename T>
void init(T* a){
	a[0] = 0;
	a[1] = 0;
	for(int i = 0; i < 4; i++)
		cout << a[i] << endl;
}

int main(){
	int* A = new int [4];
	init(A);
}
