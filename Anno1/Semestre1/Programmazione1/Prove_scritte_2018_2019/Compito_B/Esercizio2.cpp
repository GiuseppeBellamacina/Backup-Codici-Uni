#include <iostream>

using namespace std;

bool check(string s) {
    for(int i = 0; i < s.length(); i++) {
        if((int)('a') <= (int)(s[i]) && (int)('z') >= (int)(s[i])) {
            return false;
        }
    }
    return true;
}

int esercizio2(string*** A, int n, int m, short p) {
    int col = 0;
    for(int j = 0; j < m; j++) {
        int seqlen = 0;
        for(int i = 0; i < n; i++) {
            if(check(*A[i][j])) seqlen++;
        }
        if(seqlen >= p) col++;
    }
    return col;
}

void printMatrixPtr(string*** M, int n, int m) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(M[i][j])
                cout << *M[i][j] << " \t";
            else
                cout << "* \t"; 
        }
        cout << endl;
    }
}

int main() {
    int n = 3;
    int m = 3;
    short p = 2;
    string*** M = new string**[n];
    for(int i = 0; i < n; i++) M[i] = new string*[m];
    M[0][0] = new string("CASA");
    M[0][1] = new string("ORO");
    M[0][2] = new string("Oo");
    M[1][0] = new string("AbeA");
    M[1][1] = new string("abeiok");
    M[1][2] = new string("PIANO0123456789");
    M[2][0] = new string("OssA");
    M[2][1] = new string("aLa");
    M[2][2] = new string("CIAO");
    printMatrixPtr(M, n, m);
    cout << "Il numero di colonne che soddisfano la condizione del testo sono: " << esercizio2(M, n, m, p) << endl;
}