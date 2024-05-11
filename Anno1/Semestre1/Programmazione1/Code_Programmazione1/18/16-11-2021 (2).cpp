#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

#define N 10
#define M 5

using namespace std;

void f1(int w[][M], int n) { //funzione di inizializzazione matrice
	for (int j = 0; j < M; j++) {
		for (int i = 0; i < n; i++) {
			*(*(w + i) + j)  = rand() % 10; //*(*(w + i) + j) = *(w[i] + j) = w[i][j]
		}
	}
}

void stampa(int w[][M], int n){ //funzione di rappresentazione
	for(int j = 0; j < n; j++){
		for (int i = 0; i < M; i++) {
			cout<<"[ "<<w[i][j]<<" ]"<<"   ";
		}
		cout << endl;
	}
}

int main(){
	int v[N][M];
	srand(time(0));
	f1(v, N);
	stampa(v, N);
}
