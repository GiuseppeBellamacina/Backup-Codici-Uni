#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

#define N 10

using namespace std;

void f1(int *w, int n){ //funzione di inizializzazione array (0-30)
	for(int i = 0; i < n; i++){
		w[i] = rand()%31;
	}
}

void stampa(int w[], int n){ //funzione di rappresentazione
	for(int i = 0; i < n; i++){
		cout<<"[ "<<w[i]<<" ]"<<"   ";
	}
}

int main(){
	int v[50]; //allocazione automatica
	srand(time(0));
	f1(v, N);
	stampa(v, N);
	cout<<endl;
	f1(v, 13);
	stampa(v, 13);
}
