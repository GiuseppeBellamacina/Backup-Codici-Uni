#include <iostream>
#include <cstdlib>
#include <ctime>
#define N 3
#define M 5

using namespace std;

int func(double*** A, int n, int m, short k, double q){
	int ret = 0;
	for(int i = 0; i < m-n+1; i++){
		for(int z = 0; z+k <= n; z++){
			double sum = 0;
			for(int j = 0; j < k; j++){
				if(A[j+z][j+i+z]){
					sum += *A[j+z][j+i+z];
				}
			}
			if (sum / k > q)
				ret++;
		}
	}
	return ret;
}

int main(){
	srand(time(0));
	double*** A = new double** [N];
	for(int i = 0; i < N; i++){
		A[i] = new double* [M];
	}
	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			A[i][j] = new double(rand() % 10);
		}
	}
	cout << endl;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			cout << *A[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	
	cout << func(A, 3, 5, 1, 4);
}
