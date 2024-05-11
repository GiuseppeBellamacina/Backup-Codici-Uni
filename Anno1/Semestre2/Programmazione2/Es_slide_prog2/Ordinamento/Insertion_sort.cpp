#include <iostream>
#include <cstdlib>
#include <ctime>
#define DIM 10
using namespace std;

// Insertion Sort normale
void insertionSort(int A[], int n){
	for(int i=1; i<n; i++){ // si comincia da 1 perchè il primo el si considera come il primo vettore già ordinato
		int aux = A[i]; // si assegna ogni volta l'el considerato ad aux
		int j = i-1; // si assegna i-1 a j così da delimitare la sezione già ordinara del vettore
		while(j >= 0 && A[j] > aux){ // si prosegue fino a quando non si arriva all'inizio del vettore, o si trova un el < di aux
			A[j+1] = A[j]; // si sposta ogni elemento di un posto a destra
			j--;
		}
		A[j+1] = aux; // dopo aver spostato tutto si mette aux in posizione j+1 che alla fine del while è vuota
	}
}

// Funzione di ricerca binaria della posizione nel vettore ordinato in cui mettere l'el
int binaryPos(int v[], int el, int l, int h){
	if(h <= l) return el > v[l] ? l+1 : l; // se h e l coincidono controllo se el è > di v[l], in caso mi torna l+1, altrimenti l
	int m = (l+h)/2; // definisco una posizione centrale
	if(el == v[m]) return m+1; // se trovo l'el allora torno la pos successiva (se avessi tornato m non cambiava)
	if(el < v[m]) return binaryPos(v,el,l,m-1); // se el è < di v[m], allora ripeto la scansione nel settore inferiore
	return binaryPos(v,el,m+1,h); // altrimenti ripeto la scansione nel settore superiore
}

// Insertion Sort con ricerca binaria
void insertionSortBinary(int A[], int n){
	for(int i=1; i<n; i++){ // si comincia da 1 perchè il primo el si considera come il primo vettore già ordinato
		int aux = A[i]; // si assegna ogni volta l'el considerato ad aux
		int j = i-1; // si assegna i-1 a j così da delimitare la sezione già ordinara del vettore
		int pos = binaryPos(A,aux,0,j); // sfrutto la funzione per trovare la posizione in cui inserire aux
		while(j >= pos){ // si procede finchè si raggiunge la posizione cercata
			A[j+1] = A[j]; // si sposta ogni elemento di un posto a destra
			j--;
		}
		A[j+1] = aux; // dopo aver spostato tutto si mette aux in posizione j+1 che alla fine del while è vuota
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
	//insertionSort(A,DIM);
	insertionSortBinary(A,DIM);
	print(A,DIM);
	
	return 0;
}
