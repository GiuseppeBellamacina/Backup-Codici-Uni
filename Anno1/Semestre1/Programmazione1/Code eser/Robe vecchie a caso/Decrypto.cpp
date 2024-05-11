#include <iostream>
#include <limits>
#include <cstdlib>

using namespace std;

int main() {
	unsigned int pin, i = 0, j; //prova numeri non troppo grandi
	bool decrypting = true;
	cout << "Inserire PIN: ";
	cin >> pin;
	while (cin.fail() || pin > 9999) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> pin;
	}
	while (decrypting) {
		j = rand()%(pin+1);
		cout << j << endl;
		if (j == pin) {
			decrypting = false;
		}
		i++;
	}
	cout << "\nNumero tentativi: " << i << endl;
	cout << "\nIl PIN e' " << j;
	cin >> j;
}
