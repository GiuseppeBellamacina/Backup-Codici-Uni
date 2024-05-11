#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int*** esercizio1(int*** A, int n, int m, short k, int a, int b) {
    int*** C = new int**[n];
    for(int i = 0; i < n; i++) C[i] = new int*[m];
    for(int j = 0; j < m; j++) {
        bool mdec = false;
        for(int i = 0; i < n; i++) {
            int seqlen = 0;
            if(A[i][j]) {
                for(int k = i + 1; k < n - 1; k++) {
                    if(A[k][j] && *A[k-1][j] <= *A[k][j]) seqlen++;
                    else break;
                }
            }
            if(seqlen + 1 >= k) {
                mdec = true;
                break;
            }
        }
        for(int i = 0; i < n; i++) {
            if(A[i][j])
                C[i][j] = mdec ? new int(rand() % (b - a + 1) + a) : A[i][j];
            else
                C[i][j] = A[i][j];
        }
    }
    return C;
}

void printMatrixPtr(int*** M, int n, int m) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(M[i][j])
                cout << *M[i][j] << " ";
            else
                cout << "* "; 
        }
        cout << endl;
    }
}

int main() {
    srand(time(0));
    int n = 4;
    int m = 2;
    short k = 3;
    int a = 1;
    int b = 5;
    int*** A = new int**[n];
    for(int i = 0; i < n; i++) {
        A[i] = new int*[m];
    }
    A[0][0] = new int(1);
    A[1][0] = new int(2);
    A[2][0] = new int(2);
    A[3][0] = NULL;
    A[0][1] = new int(1);
    A[1][1] = NULL;
    A[2][1] = new int(2);
    A[3][1] = new int(2);

    cout << "Matrice di partenza:" << endl;
    printMatrixPtr(A, n, m);
    cout << endl << "Matrice risultante:" << endl;
    int*** C = esercizio1(A, n, m, k, a, b);
    printMatrixPtr(C, n, m);
}