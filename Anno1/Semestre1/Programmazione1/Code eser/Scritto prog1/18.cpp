/*
18.Scrivere un metodo che prenda in input una 
matrice di puntatori a stringhe M e due numeri short 
senza segno, k ed s, e restituisca il numero di colonne 
contenenti almeno k stringhe con un numero di lettere 
vocali minore di s.
*/

#include <iostream>
#include <cctype>

using namespace std;

int f1(string ***M, int n, int m, unsigned short k, unsigned short s){
	int counter = 0;
	for(int j = 0; j < m; j++){
		int stringhe = 0;
		for(int i = 0; i < n; i++){
			int vocali = 0;
			if(M[i][j]){
				for(int z = 0; z < M[i][j]->length(); z++){
					switch(toupper((*M[i][j])[z])){
						case 'A':
						case 'E':
						case 'I':
						case 'O':
						case 'U':
							vocali++;
					}
				}
			}
			if(vocali < s){
				stringhe++;
			}
		}
		if(stringhe >= k){
			counter++;
		}
	}
	return counter;
}

int main(){
	string*** M = new string **[2];
	for(int i = 0; i < 2; i++){
		M[i] = new string *[3];
	}
	
	for(int i = 0; i < 2; i++){
		for (int j = 0; j < 3; j++){
			string s = "";
			cout<<"M["<<i<<"]["<<j<<"]: ";
			cin>>s;
			M[i][j] = &s;
		}
	}
	cout<<f1(M, 2, 3, 2, 4);
}
