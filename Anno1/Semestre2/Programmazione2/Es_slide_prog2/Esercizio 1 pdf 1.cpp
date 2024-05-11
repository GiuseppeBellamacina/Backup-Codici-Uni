#include <iostream>
#define MAX_N 100

using namespace std;

/*Scrivere un programma che sfrutta un metodo ‘leggiElementi()’ per inizializzare un array
di double di dimensione non nota, chiedendo all’utente di inserire un valore per volta
fino a quando non viene inserito il valore zero. Successivamente, stampare gli elementi
mediante un altro metodo ‘stampaElementi()’*/

//int leggiElementi(double v[]){
void leggiElementi(double v[], int& num){
	cout << "Inserisici elementi uno per volta,"
		 << " quando hai finito inserisci 0." << endl;
	//int num;
	//for(num = 0; num < MAX_N; num++){
	for(num = 0; num < MAX_N; num++){
		cout << "Elementi da inserire:\t";
		cin >> v[num];
		if(v[num] == 0) break;
	}
	//return num;
}

void stampaElementi(double v[], int num){
	for(int i = 0; i < num; i++){
		cout << "v[" << i << "]:\t" << v[i] << endl;
	}
}

int main(){
	double vettore[MAX_N];	//la locazione di memoria deve essere riservata prima del metodo
	int n;
	leggiElementi(vettore, n);
	cout << "Il vettore contiene\t" << n << "\t elementi, che sono:" << endl;
	stampaElementi(vettore, n);
	
	return 0;
}
