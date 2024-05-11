#include <iostream>
#include <iomanip>
#define DIM 4

using namespace std;

int main(){
	int A[DIM][DIM]; //Inizializzazione matrice
	int k = 0;
	for(int i = 0; i < DIM; i++){
		for(int j = 0; j < DIM; j++){
			A[i][j] = ++k;
		}
	}
	
	cout << "Matrice:" << endl; //Stampa matrice
	for(int i = 0; i < DIM; i++){
		for(int j = 0; j < DIM; j++){
			cout << setw(4) << A[i][j];
		}
		cout << endl;
	}
	cout << endl;
	
	//Diagonale principale
	cout << "Diagonale principale:" << endl;
	for(int i = 0; i < DIM; i++){
		cout << setw(4) << A[i][i];
	}
	cout << endl << endl;
	
	//Diagonale secondaria
	cout << "Diagonale secondaria:" << endl;
	for(int i = 0; i < DIM; i++){
		cout << setw(4) << A[i][DIM - i - 1];
	}
	cout << endl << endl;
	
	//Parallele soprastanti la diagonale principale
	cout << "Parallele soprastanti la diagonale principale:" << endl;
	int a = 1;
	for(int k = a; k < DIM; k++){
		for(int i = 0; i < DIM - a; i++){
			cout << setw(4) << A[i][i + a];	
		}
		cout << endl;
		a++;
	}
	cout << endl;
	
	//Parallele sottostanti la diagonale principale
	cout << "Parallele sottostanti la diagonale principale:" << endl;
	a = 1;
	for(int k = a; k < DIM; k++){
		for(int i = a; i < DIM; i++){
			cout << setw(4) << A[i][i - a];	
		}
		cout << endl;
		a++;
	}
}
