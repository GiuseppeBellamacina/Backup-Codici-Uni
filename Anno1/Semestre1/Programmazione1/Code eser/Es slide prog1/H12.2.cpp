#include <iostream>

using namespace std;

int main() {
	double a, b, c;
	cout << "Inserire 3 numeri:\n";
	cin >> a >> b >> c;
	cout << static_cast<int>(a+0.5)<< endl << static_cast<int>(b+0.5) << endl << static_cast<int>(c+0.5);
}