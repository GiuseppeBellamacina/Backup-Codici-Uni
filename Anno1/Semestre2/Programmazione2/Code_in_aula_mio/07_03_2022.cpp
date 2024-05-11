//Array definizioni e operazioni varie

#include <iostream>
#define N 10

using namespace std;

int main(){
	//Definizione Array
	int array_1[5];
	int array_2[N];
	
	cout << "Array 1 len:\t" << sizeof(array_1) / sizeof(int) << endl;
	cout << "Array 1 len:\t" << sizeof(array_1) / sizeof(*array_1) << endl;
	
	cout << "Array 2 len:\t" << sizeof(array_2) / sizeof(*array_2) << endl;
	cout << "Size of int:\t" << sizeof(int) << endl;
	
	//Inizialiazzaione Array
	for(int i  = 0; i < 5; i++){
		array_1[i] = i + 1;
		array_2[i] = i * 2;
	}
	
	cout << "\nContenuto Array 1:" << endl;
	for(int i = 0; i < 5; i++){
		cout << "Indice " << i << ":\t" << array_1[i] << endl;
	}
	for(int i = 0; i < N; i++){
		cout << "Indice " << i << ":\t" << array_1[i] << endl;
	}
	
	cout << "\nContenuto Array 2:" << endl;
	for(int i = 0; i < N; i++){
		cout << "Indice " << i << ":\t" << array_2[i] << endl;
	}
	cout << endl;
	
	//Inizialiazzazione parziale
	int numeri_1[6] = {10, 20, 30, 40, 50, 60};
	int numeri_2[6] = {10, 20, 30};
	int numeri_3[] = {10, 20, 30, 40, 50, 60};
	
	for(int i = 0; i < 6; i++){
		cout << "num_1[" << i << "]:\t" << numeri_1[i] << "\t";
		cout << "num_2[" << i << "]:\t" << numeri_2[i] << "\t";
		cout << "num_3[" << i << "]:\t" << numeri_3[i] << endl;
	}
	cout << endl;
	
	cout << "Contenuto tabella [2x5]:";
	int tabella[][5] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	for(int i = 0; i < 2; i++){
		cout << endl;
		for(int j = 0; j < 5; j++){
			cout << tabella[i][j] << " ";
		}
	}
	cout << endl << endl;
	
	int x = 10;
	int *p_1 = &x;
	int *p_2 = new int[3];
	for(int i = 0; i < 3; i++){
		p_2[i] = 5;
	}
	
	cout << "Contenuto dell'array puntato da p_2:" << endl;
	for(int i = 0; i < 3; i++){
		cout << p_2[i] << endl;
	}
	
	int p_3[] = {7, 7, 7};
	int p_4[][2] = {1, 2, 3, 4, 5, 6};
	
	//Errore: il compilatore non sa quanto spazio allocare
	//int **p_5 = {{1,2}, {3,4}, {5,6}};
	int **p_5 = new int* [3];
	for(int i = 0; i < 3; i++){
		p_5[i] = new int[6];
	}
	
	int a = 5, b = 10;
	int *p_6[] = {&a, &b};
	int (*p_7)[5];  //p_7 è un puntatore ad un array di 5 interi
	int arr[5] = {1, 2, 3, 4, 5};
	p_7 = &arr;
	
	/*
	int x[]		arr
	int *x[]	arr di puntatori
	int (*x)	puntatore
	int (*x)[]	puntatore ad array
	*/
	
	return 0;
}
