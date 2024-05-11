#include <iostream>
#include <iomanip>

using namespace std;

int main() {
	double x, y, z, t;
	unsigned int i = 0, j = 0;
	bool underflow = true, overflow = true;
	cout << "Inserire un numero con la virgola: ";
	cin >> y;
	t = y;
	cout << "Inserire un altro numero minore di 1 (ma maggiore di 0) con la virgola: ";
	cin >> x;
	cout << "Inserire un altro numero ancora maggiore di 1 con la virgola: ";
	cin >> z;
	while (underflow) {
		y = y * x;
		cout << scientific << y << endl;
		i++;
		if (y == 0) {
			underflow = false;
		}
	}
	cout << "------------------------------------------------\n";
	while (overflow) {
		z = z / (x * t);
		cout << scientific << z << endl;
		j++;
		if (z == INFINITY) {
			overflow = false;
		}
	}
	cout << "Sono state necessarie " << i << " iterazioni per raggiungere l'underflow.\n";
	cout << "Sono state necessarie " << j << " iterazioni per raggiungere l'overflow.";
}