#include <iostream>
#include <cmath>
using namespace std;

int func01(int**** A, int n, short q){
	double ma = 0;
	short c = 0;
	for(int i=0; i<n; i++){
		if(A[i][i][i]){
			ma += *A[i][i][i];
			c++;
		}
	}
	if(c == 0) return -1;
	else ma /= c;
	c = 0;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			for(int k=0; k<n; k++){
				if(A[i][j][k]){
					if(abs(*A[i][j][k] - ma) <= q)
						c++;
				}
			}
		}
	}
	return c;
}

int func02(string* A, int n, int& m){
	// no, io mi rifiuto
}

int main(){
	return 0;
}
