#include <iostream>
#define N 3
//18-06-2018 <1>
using namespace std;

int* funzione(int A[N][N], int B[N]) {
    int *C = new int[N];
    int z = 0;
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (A[i][j] == B[k]) {
                    C[z] == B[k];
                    z++;
                }
            }
        }
    }
    return C;
}

int main() {
    int C[N];
    int A[3][3] = { {2,2,5}, {4,5,6}, {7,7,9} };
    int B[3] = { 5,6,7 };
    funzione(A, B);
    for (int i = 0; i < N; i++) {
        cout << C[i] << endl;
    }
}