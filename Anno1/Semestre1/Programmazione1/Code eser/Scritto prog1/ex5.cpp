#include <iostream>

using namespace std;

int* func(int** A, int n, int m, double** B, int k){
	int* ret = new int [n];
	for(int i = 0; i < n; i++){
		int counter = 0;
		int media = 0;
		for(int j = 0; j < m; j++){
			for(int z = 0; z < k; z++){
				if(A[i][j] == ((int) (B[z][i] + 0.5))){
					counter++;
					media += A[i][j];
				}
			}
		}
		if(counter)
			media /= counter;
		ret[i] = media;
	}
	return ret;
}

int main(){
	
}
