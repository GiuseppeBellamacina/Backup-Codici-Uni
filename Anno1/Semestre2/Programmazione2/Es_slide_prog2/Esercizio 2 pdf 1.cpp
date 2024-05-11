#include <iostream>
#include <cmath>

using namespace std;
bool print;

/*Definire più metodi per stampare i primi n numeri primi, e valutare il loro tempo di
esecuzione per valori di n crescenti.*/

/*	Metodo 1:
	per ogni numero num da 2 a n:
	cerca un divisore di num dentro [2, num/2]
	se non lo trovo, num è primo.
*/
void metodoNmezzi(int n){
	int num = 2;
	int div;
	bool primo = true;
	int lim;
	
	while(num <= n){
		//cerco un div che divide num in [2, num/2]
		div = 2;
		primo = true;
		lim = floor(num/2);
		while(div <= lim){ //floor rende l'approssimazione più sicura
			if(num % div == 0){
				primo = false;
				break;
			}
			div++;
		}
		if(primo)
			cout << num << "\t";
		num++;
	}
}

/*	Metodo 2:
	sia num intero in [1, n]
	n = sqrt(num) * sqrt(num);
	n = a*b		num, a, b interi > 1
	se uno tra a e b è > sqrt(num), allora l'altro deve essere < sqrt(num)
	quindi cerchiamo l'altro, che si troverà in [2, sqrt(num)]
*/
void metodoSqrt(int n){
	int num = 2, div;
	bool primo;
	int lim;
	while(num <= n){
		div = 2;
		primo = true;
		lim = (int)sqrt(num);
		while(div <= lim){
			if(num % div == 0){
				primo = false;
				break;
			}
			div++;
		}
		if(primo)
			cout << num << "\t";
		num++;
	}
}

/*	Metodo 3: Crivello di Eratostene
	elenco tutti i numeri da 2 a n
	elimino i multipli di 2
	elimino i multipli di 3
	...
	appena trovo il primo numero che non ha multipli mi fermo
*/
void eratostene(int n){
	int i;
	//vec mi dice se un numero è primo oppure no
	bool vec[n];
	for(int i = 2; i < n; i++) vec[i] = true;
	for(int i = 2; i < n; i++)
		if(vec[i]){
			for(int j = i; j*i < n; j++)
				/*
					i = 2	i*j = 2*2  2*3  ...
					i = 3	i*j = 3*3  2*4
				*/
				vec[i*j] = false;
		}
		for(int i = 2; i < n; i++)
			if(vec[i] && print)
				cout << i << "\t";
		
}

int main(){
	int n;
	print = true;
	cout << "Inserisci n: ";
	cin >> n;
	if(n > 100)
		print = false;
	cout << "Numeri primi fino a " << n << ":" << endl;
	metodoNmezzi(n);
	
	cout << endl << "Numeri primi fino a " << n << ":" << endl;
	metodoSqrt(n);
	
	cout << endl << "Crivello di Eratostene:" << endl;
	cout << "Numeri primi fino a " << n << ":" << endl;
	eratostene(n);
	
	return 0;
}
