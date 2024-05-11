#include <iostream>
#include <ctime>
#include <math.h>
using namespace std;

void CountingSort(int *A, int n) {
	int min = A[0];
	int max = A[0];
	for(int i=1; i<n; i++) {
		if(A[i]>max) max= A[i];
		if(A[i]<min) min= A[i];
	}
	int range = max-min+1;
	int *C = new int[range];
	for(int i=0; i<range; i++) C[i]=0;
	for(int i=0; i<n; i++) C[A[i]-min]++;
	int j=0;
	for(int k=0; k<range; k++) {
		while(C[k]>0) {
			A[j++] = k+min;
			C[k]--;
		}
	}
}

void print(int *A, int n) {
	cout << "A: ";
	for(int i=0; i<n; i++)
		cout << A[i] << " ";
	cout << endl;
}

int main() {
	int A[] = {5, 7, 12, 45, 21, 2, 3, 20, 18, 13};
	int n = 10;
	print(A,n);
	CountingSort(A,n);
	print(A,n);
	
}
