#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

#define N 5
#define M 7

using namespace std;

int main() {
	double A[N][M];
	double pippo_natale;
	srand(time(0)); //seme coso random
	//inizializzazione a cazzo de cane della matrice
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			A[i][j] = rand() / (RAND_MAX * 1.0) * 10;
		}
	}
	//rappresentaziona matrice per come si deve
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << setw(10) << fixed << setprecision(4) << A[i][j];
		}
		cout << endl;
	}
	cout << "Senti mbare ora scelgo un numero a caso, perche' si" << endl << "Ci sto pensando...\n";
	pippo_natale = rand() / (RAND_MAX * 1.0) * 10;
	cout << "Ok mbare il numero a caso perche' si e' " << pippo_natale << endl;
	//moltiplicazione a cazzzo
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			A[i][j] *= pippo_natale;
		}
	}
	//rappresentaziona matrice nuova per come si deve
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << setw(10) << fixed << setprecision(4) << A[i][j];
		}
		cout << endl;
	}
	cout << endl;
	//rappresentaziona matrice nuova per come si deve ma più piccola
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << setw(10) << fixed << setprecision(4) << A[i][j];
		}
		cout << endl;
	}
}