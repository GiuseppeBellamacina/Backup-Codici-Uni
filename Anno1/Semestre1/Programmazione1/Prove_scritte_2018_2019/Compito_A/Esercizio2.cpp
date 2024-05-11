#include <iostream>

using namespace std;

bool checkPalindroma(string s) {
    int mid = s.length()/2;
    int j = s.length() - 1;
    string p = s;
    for(int i = 0; i < mid; i++) {
        char tmp = s[i];
        s[i] = s[j];
        s[j--] = tmp; 
    }
    return p == s;
}

int esercizio2(string*** M, int n, int m, short k, short r, short s) {
    int col = 0;
    for(int j = 0; j < m; j++) {
        int cont_pal = 0;
        for(int i = 0; i < n; i++) {
            if(M[i][j] && M[i][j]->length() >= r && M[i][j]->length() <= s && checkPalindroma(*M[i][j]))
                cont_pal++;
        }
        if(cont_pal >= k) col++;
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
    short r = 3;
    short s = 8;
    short k = 2;
    string*** M = new string**[n];
    for(int i = 0; i < n; i++) M[i] = new string*[m];
    M[0][0] = new string("casa");
    M[0][1] = new string("oro");
    M[0][2] = new string("oo");
    M[1][0] = new string("abekeba");
    M[1][1] = new string("abeiokoieba");
    M[1][2] = new string("piano");
    M[2][0] = new string("ossa");
    M[2][1] = new string("ala");
    M[2][2] = new string("ciao");
    printMatrixPtr(M, n, m);
    cout << "Il numero di colonne che soddisfano la condizione del testo sono: " << esercizio2(M, n, m, k, r, s) << endl;
}