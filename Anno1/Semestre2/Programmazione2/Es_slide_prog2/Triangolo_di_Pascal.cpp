#include <iostream>
#define N 7

using namespace std;

void print(int* vec, int n, int riga){ // si tratta della funzione di stampa dell'array
	int k = N - 1;
	string tab = "";
	for(int i = 0; i < k - riga; i++)
		tab += "\t";
	cout << tab;
	for(int i = 0; i < n; i++)
		cout << vec[i] << "\t\t";
	cout << endl;
}

void arrCopy(int* vec1, int* vec2, int n){ // serve a copiare il secondo array sul primo
	for(int i = 0; i < n; i++)
		vec1[i] = vec2[i];
}

void pascal(int n){
	int vec[N];
	int aux[n] = {0}; // creo un array ausilario
	arrCopy(vec, aux, n); // copio su vec l'inizializzazione di aux
	int k = n-1; // serve a settare la lunghezza delle righe (vedi sotto)
	for(int riga = 0; riga < n; riga++, k--){ // ogni ciclo del for è una riga (continuo...)
		aux[0] = 1, vec[0] = 1;				  // (...continuo) N.B. decremento k ad ogni ciclo
		for(int i = 1; i < n-k; i++) // uso n-k perchè a seconda della riga, avrò solo n-k elementi
			vec[i] = aux[i-1] + aux[i]; // assegno all'i-esimo elemento dell'array il valore corretto
		print(vec, n-k, riga); // N.B. uso n-k perchè è la lunghezza che mi basta stampare per la singola riga del triangolo
		arrCopy(aux, vec, n-k); // N.B. uso n-k perckè mi basta solo quella (continuo...)
								// (...continuo) porzione di array da copiare e usare al prossimo ciclo
	}
}

int main(){
	pascal(N);
	return 0;
}
