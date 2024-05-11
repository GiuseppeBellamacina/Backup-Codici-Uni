#include <iostream>
using namespace std;

// Ordinamento per inserimento
void insertionSort(int A[], int n){
	/*
	[   |   |   |   |   ]
	    ^
	    i
	A[0...i-1] : identifica un sottoarray ordinato
	*/
	int chiave, i, j;
	for(i=1; i<n; i++){
		chiave = A[i]; // elemento da posizionare
		
		/*
		       <--j
			[.....|.....]
			      ^
			      i
		*/
		j = i-1;
		while(j >= 0 && A[j] > chiave){
			A[j+1] = A[j];
			j--;
		}
		A[j+1] = chiave;
	}
}

// Migliorare l'algoritmo precedente sfruttando la ricerca binaria

int binarySearch(int a[], int chiave, int l, int h){ // ricerca binaria per trovare la pos di chiave
	if(h <= l) // ci si riduce ad un solo elemento
		return chiave > a[l] ? l+1 : l;
	int m = (l+h)/2;
	if(chiave == a[m]) return m+1;
	if(chiave > a[m])
		return binarySearch(a, chiave, m+1, h);
	else
		return binarySearch(a, chiave, l, m-1);
}

void insertionSortBinario(int a[], int n){
	int i,j,chiave;
	for(int i=1; i<n; i++){
		chiave = a[i];
		j = i-1;
	
		//trovare la posizione dove inserire la chiave
		int pos = binarySearch(a, chiave, 0, j);
	
		// sposto gli elementi a dx di 1 posizione
		// per fare spazio alla chiave
		while(j >= pos){
			a[j+1] = a[j];
			j--;
		}
		a[j+1] = chiave;
	}
}

void stampaVettore(int v[], int n){
	for(int i=0; i<n; i++)
		cout << v[i] << "  ";
}

int main(){
	int vettore[20] = {12,3,6,7,130,4,120,11,0,9,10,16,71,89,15,24,10,21,2,13};
	
	cout << "Vettore iniziale:\t";
	stampaVettore(vettore,20);
	
	/*insertionSort(vettore,20);
	cout << "\nVettore ordinato:" << endl;
	stampaVettore(vettore,20);*/
	
	insertionSortBinario(vettore,20);
	cout << "\nVettore ordinato\t";
	stampaVettore(vettore,20);
	
	return 0;
}
