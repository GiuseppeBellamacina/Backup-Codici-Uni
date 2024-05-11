#include <iostream>
#include <cstring>
#define D 60
#define P 120

using namespace std;

int main() {
	unsigned short uno = 0, due = 0, tre = 0, quattro = 0, cinque = 0;
	unsigned short A[5], B[5], i, j;
	double tempo, a = 0, b = 0, c = 0;
	cout << "Sciao mbare, inserisci 5 numeri differenti compresi tra 1 e 15:\n" << "Tubo 1: ";
	cin >> uno;
	while (uno < 1 || uno>15 || cin.fail()) {
		cout << "Valore non consentito.\n";
		cout << "Tubo 1: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> uno;
	}
	A[0] = uno;
	B[0] = uno;
	cout << "Tubo 2: ";
	cin >> due;
	while (due < 1 || due > 15) {
		cout << "Valore non consentito.\n";
		cout << "Tubo 2: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> due;
	}
	A[1] = due;
	B[1] = due;
	cout << "Tubo 3: ";
	cin >> tre;
	while (tre < 1 || tre > 15) {
		cout << "Valore non consentito.\n";
		cout << "Tubo 3: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> tre;
	}
	A[2] = tre;
	B[2] = tre;
	cout << "Tubo 4: ";
	cin >> quattro;
	while (quattro < 1 || quattro > 15) {
		cout << "Valore non consentito.\n";
		cout << "Tubo 4: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> quattro;
	}
	A[3] = quattro;
	B[3] = quattro;
	cout << "Tubo 5: ";
	cin >> cinque;
	while (cinque < 1 || cinque > 15) {
		cout << "Valore non consentito.\n";
		cout << "Tubo 5: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> cinque;
	}
	A[4] = cinque;
	B[4] = cinque;
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			if (A[i] == A[j] && i!=j) {
				cout << "Ooops:\n"
					 << "Tubo " << i + 1 << " uguale a Tubo " << j + 1 <<".\nRiprova.\n\n";
				return main();
			}
		}
	}
	cout << "Dimmi per quanto tempo deve scorrere l'acqua (min): ";
	cin >> tempo;
	while (tempo < 0 || cin.fail()) {
		cout << "Quantita' di tempo non valida." << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Dimmi per quanto tempo deve scorrere l'acqua (min): ";
		cin >> tempo;
	}
	for (i = 0; i < 5; i++) {
		if (A[i] % 2 != 0) {
			A[i] = tempo * D;
		}
		else {
			A[i] = tempo * P;
		}
		switch (B[i]) {
		case 1:
			a += A[i];
			break;
		case 2:
		case 3:
		case 4:
			b += A[i];
			break;
		case 5:
		case 6:
			a += A[i];
			break;
		case 7:
		case 8:
		case 9:
			b += A[i];
			break;
		case 10:
			a += A[i];
			break;
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
			c += A[i];
			break;
		}
	}
	cout << " La vasca A ha ricevuto " << a << " litri d'acqua.\n";
	cout << " La vasca B ha ricevuto " << b << " litri d'acqua.\n";
	cout << " La vasca C ha ricevuto " << c << " litri d'acqua.\n";
}