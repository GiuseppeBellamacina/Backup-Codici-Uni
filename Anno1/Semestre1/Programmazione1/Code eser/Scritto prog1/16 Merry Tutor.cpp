#include <iostream>
#include <string>

using namespace std;

bool esercizio16(string ***A, int n, int m, char c) {
    string *S = new string[n*m];
    int k = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            string s = *A[i][j];
            while(s.find(c) != string::npos) {
                s.erase(s.find(c), 1);
            }
            S[k++] = s;
        }
    }
    for(int i = 0; i < k; i++) {
        for(int j = i + 1; j < k; j++) {
            if(S[i] == S[j]) return true;
        }
    }
    return false;
}

int main() {
    string*** M = new string**[4];
    string input = "";
    for(int i = 0; i < 4; i++) {
        M[i] = new string*[3];
        for(int j = 0; j < 3; j++) {
            cout << "Inserisci un valore per la posizione [" << i << "][" << j << "]: ";
            cin >> input;
            M[i][j] = new string(input);
        }
    }
    char c = 'c';
    cout << esercizio16(M, 4, 3, c) << endl;
}
