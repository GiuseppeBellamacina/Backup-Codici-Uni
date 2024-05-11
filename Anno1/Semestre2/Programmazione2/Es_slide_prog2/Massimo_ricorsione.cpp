#include <iostream>
#define N 5

using namespace std;

int listMax(int* v, int left, int right){
	if (left == right) return v[left];
	else{
		int middle = (left + right)/2;
		int max_l = listMax(v, left, middle);
		int max_r = listMax(v, middle+1, right);
		return (max_l < max_r ? max_r : max_l);
	}
}

int main(){
	int A[N] = {1,2,3,4,5};
	cout << listMax(A, 0, N-1);
}
