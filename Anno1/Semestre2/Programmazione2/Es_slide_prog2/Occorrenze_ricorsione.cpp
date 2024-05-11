#include <iostream>

using namespace std;

/*
calcolare il numero di occorrenze di un carattere c in una stringa s
*/

int occ(string s, char c, int i = 0){
	if(s.length() == i) return 0;
	else{
		if(s[i] == c)
			return 1 + occ(s, c, i+1);
		return occ(s, c, i+1);
	}
}

int main(){
	cout << "Inserisci stringa: ";
	string s;
	cin >> s;
	cout << "Inserisci carattere: ";
	char c;
	cin >> c;
	cout << occ(s, c);
}
