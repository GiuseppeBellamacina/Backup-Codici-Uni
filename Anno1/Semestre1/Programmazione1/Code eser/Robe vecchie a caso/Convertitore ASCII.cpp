#include <iostream>
#define YES1 'Y'
#define YES2 'y'

using namespace std;

int main() {
	char car, risposta;
	int cod;
	cout << "Sciao mbare, vuoi inserire una codifica ASCII (1) o un carattere (2)?\n";
	cin >> risposta;
	switch (risposta)
	{
	case '1':
		cout << "Inserisci una codifica ASCII, cosi' vediamo il carattere corrispondente: ";
		cin >> cod;
		cout << "Il carattere corrispondente alla codifica ASCII " << cod << " e' " << (char)cod << endl;
		cout << "\nVuoi fare un'altra conversione? (Y/N)\n";
		cin >> risposta;
		if (risposta != YES1 && risposta != YES2) {
			cout << "Ho capito, addios...";
		}
		else {
			cout << "Ri-";
			return main();
		}
		break;
	case '2':
		cout << "Inserisci un carattere, cosi' vediamo la sua codifica ASCII: ";
		cin >> car;
		cout << "La codifica ASCII di " << car << " e' " << (int)car << endl;
		cout << "\nVuoi fare un'altra conversione? (Y/N)\n";
		cin >> risposta;
		if (risposta != YES1 && risposta != YES2) {
			cout << "Ho capito, addios...";
		}
		else {
			cout << "Ri-";
			return main();
		}
		break;
	default:
		cout << "Mbare, devi scrivere 1 o 2\n";
		return main();
	}
	return 0;
}