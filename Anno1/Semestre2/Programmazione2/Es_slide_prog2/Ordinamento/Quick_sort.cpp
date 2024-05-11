#include <iostream>
#include <cstdlib>
#include <ctime>
#define DIM 15
using namespace std;

// Quick Sort
void swap(int v[], int i, int j){
	int aux = v[i];
	v[i] = v[j];
	v[j] = aux;
}

int partition(int v[], int l, int r){
	int x = v[r];
	int j = l-1;
	for(int i=l; i<r; i++){
		if(v[i] <= x){
			j++;
			swap(v,i,j);
		}
	}
	swap(v,j+1,r);
	return j+1;
}

void quickSort(int v[], int l, int r){
	if (l < r){
		int m = partition(v,l,r); // m è il pivot
		quickSort(v,l,m-1);
		quickSort(v,m+1,r);
	}
}

void quickSort(int v[], int n){
	quickSort(v,0,n-1);
}


// Quick Sort ALternativo
void quickSortAlt(int v[], int l, int r){
	int i = l;
	int j = r;
	int pivot = v[(l+r)/2];
	while(i <= j){
		while(v[i] < pivot) i++;
		while(v[j] > pivot) j--;
		if(i <= j){
			swap(v,i,j);
			i++, j--;
		}
	}
	if(l < j)
		quickSortAlt(v,l,j);
	if(i < r)
		quickSortAlt(v,i,r);
}

void quickSortAlt(int v[], int n){
	quickSortAlt(v,0,n-1); // serve per chiamare la funzione con 2 parametri
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
	cout << endl;
	system("pause");
	cout << "\nVettore ordinato:\t";
	//quickSort(A,DIM);
	quickSortAlt(A,DIM);
	stampa(A,DIM);
	
	return 0;
}
