#include <iostream>
#define Z 3 //profondità, numero matrici 2D
#define X 4 //altezza, numero righe
#define Y 5 //larghezza, numero colonne

using namespace std;

int main(){
	int*** A = new int **[Z];
	for(int k = 0; k < Z; k++){
		A[k] = new int *[X];
		for(int i = 0; i < X; i++){
			A[k][i] = new int [Y];
			for(int j = 0; j < Y; j++){
				A[k][i][j] = k; 	//in pratica i normali i e j (rispettivamente indice e colonna) vengono spostati a destra
			}						//k che ora è il primo indice è la profondità
		}
	}
	
	for(int k = 0; k < Z; k++){
		cout << "DIM: " << k << endl;
		for(int i = 0; i < X; i++){
			for(int j = 0; j < Y; j++){
				cout << A[k][i][j]; //k: indice profondità
			}						//i: indice riga
			cout << endl;			//j: indice colonna
		}
		cout << endl;
	}
	
	cout << endl << endl;
	cout << "Faccia superiore:" << endl;
	for(int k = Z-1; k >= 0; k--){ //comincio dal valore massimo di Z così non stampa la faccia dela figura 3D vista al contrario
		for(int j = 0; j < Y; j++){
			cout << A[k][0][j];
		}
		cout << endl;
	}
}
