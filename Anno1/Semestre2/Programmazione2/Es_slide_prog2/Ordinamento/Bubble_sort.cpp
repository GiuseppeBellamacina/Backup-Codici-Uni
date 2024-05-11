#include <iostream>
#include <cstdlib>
#include <ctime>
#define DIM 15
using namespace std;

// Bubble Sort
void bubbleSwap(int v[], int i){
	int aux = v[i];
	v[i] = v[i+1];
	v[i+1] = aux;
}

void bubbleSort(int v[], int n){
	bool flag = true;
	while(flag){
		flag = false;
		for(int i=0; i<n-1; i++){
			if(v[i] > v[i+1]){
				bubbleSwap(v,i);
				flag = true;
			}
		}
	}
}

// Stampa array
void stampa(int v[], int n){
	for(int i=0; i<n; i++)
		cout << v[i] << " ";
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
	cout << "Vettore normale:\t";
	stampa(A,DIM);
	cout << "\nVettore ordinato:\t";
	bubbleSort(A,DIM);
	stampa(A,DIM);
	
	return 0;
}
