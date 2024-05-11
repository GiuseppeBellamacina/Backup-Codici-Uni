/*
Due stringhe si dicono c-equivalenti se esse 
risultano uguali dopo aver eliminato da ambedue tutte 
le occorrenze del carattere c. Scrivere un metodo che 
prenda in input una matrice A di puntatori a stringhe 
ed un carattere c, e restituisca un boolean che indichi 
se esistono in A due stringhe c-equivalenti. 
*/
#include <iostream>

using namespace std;

bool es16(string*** A, int n, int m, char c){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			int counter = 0;
			if(A[i][j]){
				for(int z = 0; z < A[i][j]->length(); z++){
					if((*A[i][j])[z] == c){
						A[i][j]->erase(z, 1);
					}
				}
			}
			for(int l = 0; l < n; l++){
				for(int k = 0; k < m; k++){
					if(A[i][j] && A[l][k]){
						if(*A[i][j] == *A[l][k] && !(i==l && j==k)){
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

int main(){
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
    cout << es16(M, 4, 3, c) << endl;
}
