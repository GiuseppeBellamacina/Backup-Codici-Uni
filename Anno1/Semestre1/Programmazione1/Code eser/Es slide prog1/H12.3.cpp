#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {
	string nome, cognome;
	int a = 0, b = 0;
	stringstream c;
	cout << "Inserisci il tuo nome: ";
	cin >> nome;
	cout << "Inserisci il tuo cognome: ";
	cin >> cognome;
	cout << nome.substr(0, 1) << nome.substr(nome.length() - 1, 1) << endl;
	cout << cognome.substr(1, 2) << endl;
	
	while (a < nome.size()) {
		b = 0;
		while (b < cognome.size()) {
			if (nome[a] == cognome[b]) {
				c << nome[a];
			}
			b++;
		}
		a++;
	}if (c.str().size() == 0) {
		cout << "Nessuna lettera in comune\n";
	}
	else {
		cout << c.str() << endl;
	}

	if (nome[0] == cognome[cognome.size() - 1]) {
		cout << "Prima lettera del nome uguale all'ultima del cognome\n";
	}

	if (nome.size() == cognome.size()) {
		cout << "Numero di lettere del nome uguale a quello del cognome\n";
	}

	a = 0, b = 0;
	while (a < nome.size()) {
		if (nome[a] != 65 && nome[a] != 69 && nome[a] != 73 && nome[a] != 79 && nome[a] != 85 && nome[a] != 97 && nome[a] != 101 && nome[a] != 105 && nome[a] != 111 && nome[a] != 117) {
			b++;
		}
		a++;
	}
	cout << b <<endl;

	a = 0, b = 0;
	while (b < cognome.size()) {
		if (cognome[b] != 65 && cognome[b] != 69 && cognome[b] != 73 && cognome[b] != 79 && cognome[b] != 85 && cognome[b] != 97 && cognome[b] != 101 && cognome[b] != 105 && cognome[b] != 111 && cognome[b] != 117) {
			a++;
		}
		b++;
	}
	cout << a << endl;
	return 0;
} 
