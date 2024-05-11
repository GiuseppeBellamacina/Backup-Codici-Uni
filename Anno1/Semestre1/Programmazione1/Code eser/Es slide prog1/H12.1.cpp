#include <iostream>
#include <iomanip>

using namespace std;

int main() {
	double a, b;
	cout << "Inserisci due numeri con la virgola:\n";
	cin >> a >> b;
	cout << fixed << setprecision(4) << a + b << endl
		<< (a + b) / 2 << endl
		<< max(a, b) << endl;
}