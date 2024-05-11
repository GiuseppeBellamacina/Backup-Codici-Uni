#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

int main() {
	srand(time(0));
	int a = rand() % 2;
	string domanda;
	cout << "Chiedi e ti sara' rivelato il futuro" << endl <<endl;
	getline(cin, domanda);
	if (a) {
		cout << "Si" << endl;
	}
	else {
		cout << "No" << endl;
	}
}