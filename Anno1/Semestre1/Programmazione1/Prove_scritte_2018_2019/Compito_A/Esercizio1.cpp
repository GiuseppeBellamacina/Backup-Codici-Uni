#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int*** esercizio1_1(int*** M, int n, int m, int a, int b, short s) {
    int*** C = new int**[n];
    for(int i = 0; i < n; i++) C[i] = new int*[m];
    for(int j = 0; j < m; j++) {
        for(int i = 0; i < n; i++) {
            int count_s = 1;
            if(M[i][j]) {
                int check_num = *M[i][j];
                for(int k = i + 1; k < n; k++) {
                    if(M[k][j] && *M[k][j] == check_num) count_s++;
                }
                if(count_s >= s) {
                    C[i][j] = new int((rand() % (b - a + 1) + a) * (-1));
                }
                else {
                    C[i][j] = M[i][j];
                }
            }
            else {
                C[i][j] = M[i][j];
            }
        }
    }
    return C;
}

int*** esercizio1_2(int*** M, int n, int m, int a, int b, short s) {
    int*** C = new int**[n];
    for(int i = 0; i < n; i++) {
        C[i] = new int*[m];
    }
    for(int j = 0; j < m; j++) {
        for(int i = 0; i < n; i++) {
            int count_s = 1;
            if(M[i][j]) {
                int check_num = *M[i][j];
                for(int k = i + 1; k < n; k++) {
                    if(M[k][j] && *M[k][j] == check_num) count_s++;
                }
                if(count_s >= s) {
                    C[i][j] = new int((rand() % (b - a + 1) + a) * (-1));
                    for(int k = i + 1; k < n; k++) {
                        if(M[k][j]) {
                            if(*M[k][j] == check_num) {
                                if(!C[k][j])
                                    C[k][j] = new int((rand() % (b - a + 1) + a) * (-1));
                                else
                                    *C[k][j] = (rand() % (b - a + 1) + a) * (-1);
                            }
                            else {
                                C[k][j] = M[k][j];
                            }
                        }
                    }
                }
                else {
                    if(!C[i][j]) C[i][j] = M[i][j];
                }
            }
            else {
                C[i][j] = M[i][j];
            }
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
    int n = 5;
    int m = 4;
    int a = 1;
    int b = 5;
    short s = 3;
    int*** M = new int**[n];
    for(int i = 0; i < n; i++) {
        M[i] = new int*[m];
        for(int j = 0; j < m; j++) {
            M[i][j] = new int(rand() % (b - a + 1) + a);
        }
    }
    M[0][2] = NULL;
    M[0][0] = NULL;
    M[4][3] = NULL;
    cout << "Matrice di partenza:" << endl;
    printMatrixPtr(M, n, m);
    cout << endl << "Matrice risultante 1:" << endl;
    int*** C1 = esercizio1_1(M, n, m, a, b, s);
    printMatrixPtr(C1, n, m);
    cout << endl << "Matrice risultante 2:" << endl;
    int*** C2 = esercizio1_2(M, n, m, a, b, s);
    printMatrixPtr(C2, n, m);

}