#include <iostream>
#include <cstdlib>
#define N 7
#define M 4

using namespace std;

int fungo(long A[N][M], long x) {
	int cont = 0, i = 0, j = 0;
	int B[M] = {};
	int max = B[0];
	for (j = 0; j < M; j++) {
		for (i = 0; i < N; i++) {
			if (A[i][j] == x) {
				cont++;
			}
		}
		B[j] = cont;
		cont = 0;
	}
	for (j = 0; j < M; j++) {
		if (max < B[j]) {
			max = B[j];
			i = j;
		}
	}
	return i;
}

int main() {
	long A[N][M];
	srand(time(0));
	for (int i = 0; i <N ; i++) {
		for (int j = 0; j < M; j++) {
			A[i][j] = rand() % 3;
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << A[i][j] << "   ";
		}
		cout << endl;
	}
	long x = 2;
	cout << fungo(A, x);
}