#include <iostream>
#include <cstdlib>
#include <ctime>
#define DIM 10
using namespace std;

// Funzione di ricerca della posizione del minimo di una porzione di array
int findMin(int v[], int l, int n){
	int pos = l; // inizializzo la posizione del minimo
	for(int i=l+1; i<n; i++){ // comincio da l+1 per non considerare l'el di indice l
		if(v[i] < v[pos]) // controllo se trovo un nuovo minimo
			pos = i; // conservo la sua posizione
	}
	return pos; // ritorno la posizione del minimo
}

// Selection Sort
void selectionSort(int A[], int n){
	for(int i=0; i<n-1; i++){ // finisco prima di n-1 perchè l'ultimo el sarà automaticamente ordinato alla fine
		int pos = findMin(A,i,n); // prendo la posizione del minimo della porzione destra dell'array
		// le tre operazioni successive sono lo swap
		int aux = A[i];
		A[i] = A[pos];
		A[pos] = aux;
	}
}

// Selection Sort tutto in uno
void selectionSort1(int A[], int n){
	for(int i=0; i<n-1; i++){
		int pos = i;
		for(int j=i+1; j<n; j++){
			if(A[j] < A[pos]) pos = j;
		}
		int aux = A[i];
		A[i] = A[pos];
		A[pos] = aux;
	}
}

// Funzione di stampa array
void print(int v[], int n){
	for(int i=0; i<n; i++)
		cout << v[i] << endl;
}

// Funzione di inizializzazione randomica array
void initRand(int v[], int n){
	srand(time(0));
	for(int i=0; i<n; i++)
		v[i] = rand()%101;
}

int main(){
	int A[DIM];
	initRand(A,DIM);
	print(A,DIM);
	cout << "----- Vettore ordinato -----" << endl;
	//selectionSort(A,DIM);
	selectionSort1(A,DIM);
	print(A,DIM);
	
	return 0;
}
