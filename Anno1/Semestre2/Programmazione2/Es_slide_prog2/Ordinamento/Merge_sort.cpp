#include <iostream>
#include <cstdlib>
#include <ctime>
#define DIM 15
using namespace std;

// Merge Sort
void merge(int v[], int l, int m, int r){
	int dim1 = m-l+1;
	int dim2 = r-m;
	
	// Creazione array temporanei
	int* arr1 = new int[dim1];
	int* arr2 = new int[dim2];
	
	// Copia dei dati negli array temporanei
	for(int i=0; i<dim1; i++)
		arr1[i] = v[l+i];
	for(int i=0; i<dim2; i++)
		arr2[i] = v[m+1+i];
	
	// Indici array temporanei, ind è l'indice dell'array unito
	int ind1 = 0;
	int ind2 = 0;
	int ind = l;
	
	// Inserimento ordinato elementi sottoarray non vuoti
	while(ind1 < dim1 && ind2 < dim2){
		if(arr1[ind1] <= arr2[ind2]){
			v[ind] = arr1[ind1];
			ind1++;
		}
		else{
			v[ind] = arr2[ind2];
			ind2++;
		}
		ind++;
	}
	
	// Inserimento ordinato elementi sottoarray con array destro vuoto
	while(ind1 < dim1){
		v[ind] = arr1[ind1];
		ind1++;
		ind++;
	}
	
	// Inserimento ordinato elementi sottoarray con array sinistro vuoto
	while(ind2 < dim2){
		v[ind] = arr2[ind2];
		ind2++;
		ind++;
	}
	
	delete [] arr1;
	delete [] arr2;
}

void mergeSort(int v[], int l, int r){
	if(l < r){
		int m = (l+r)/2;
		mergeSort(v,l,m);
		mergeSort(v,m+1,r);
		merge(v,l,m,r);
	}
}

void mergeSort(int v[], int n){
	mergeSort(v,0,n-1);
}

//VERSIONE ALTERNATIVA
void mergeAlt(int* a, int low, int mid, int high){
	// Le due metà degli array ordinati sono da low a mid e da mid+1 a high
	int i, j, k, temp[high-low+1];
	i = low;
	k = 0;
	j = mid + 1;
	
	// Si uniscono in temp[]
	while(i <= mid && j <= high){
		if(a[i] < a[j]){
			temp[k] = a[i];
			k++, i++;
		}
		else{
			temp[k] = a[j];
			k++, j++;
		}
	}
	
	// Si mettono i valori restanti
	while(i <= mid){
		temp[k] = a[i];
		k++, i++;
	}
	
	while(j <= high){
		temp[k] = a[j];
		k++, j++;
	}
	
	for(i=low; i<=high; i++)
		a[i] = temp[i-low];
}

void mergeSortAlt(int* a, int low, int high){
	if(low < high){
		int mid = (low+high)/2;
		mergeSortAlt(a,low,mid);
		mergeSortAlt(a,mid+1,high);
		mergeAlt(a,low,mid,high);
	}
}

void mergeSortAlt(int* a, int n){
	mergeSortAlt(a,0,n-1);
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
	mergeSort(A,DIM);
	//mergeSortAlt(A,DIM);
	stampa(A,DIM);
	
	return 0;
}
