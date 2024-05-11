#include <iostream>
#include <algorithm>
#include <string>
#define BC 0.018
#define BP 0.02
#define PC 0.02
#define PP 0.022

using namespace std;

int main() {
	char risposta;
	int carico;
	double lunghezza, spessore, Q=1.0;
	cout << "Nuovo cliente\n"
		 << "-------------\n";
	cout << "Esterno (E) o interno (I)?\n";
	cin >> risposta;
	cout << "A quanto ammonta il carico massimo ?\n";
	cin >> carico;
	cout << "Quanto deve essere lungo il ripiano?\n";
	cin >> lunghezza;
	if (lunghezza < 1) {
		lunghezza = 1;
		}
	if (risposta != 'E') {
		cout << "Va impiegato legno di Pino\n";
		if (carico > 100) {
			Q = 1.1;
		}
		spessore = (BP + --lunghezza * PP) * Q;
		cout << "Lo spessore del ripiano sara' di " << spessore << " cm\n";
	}
	else {
		cout << "Va impiegato legno di Castagno\n";
		if (carico > 80) {
			Q = 1.2;
		}
		spessore = (BC + --lunghezza * PC) * Q;
		cout << "Lo spessore del ripiano sara' di " << spessore << " cm\n";
	}
	return main();
}