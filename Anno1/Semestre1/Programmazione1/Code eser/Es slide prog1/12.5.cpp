#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main() {
	stringstream ss;
	string a, b, c, x, first, second, Lupin;
	double d=0, e=0;
	unsigned short s = 0, i = 0, j = 0;
	while (s < 5) {
		x = "";
		cin >> x;
		if ((x[0] == 45) || (x[0] >= 47 && x[0] <= 58) && i==0) {
			d = stoi(x);
			i++;
		}
		else if ((x[0] == 45) || (x[0] >= 47 && x[0] <= 58) && i == 1) {
			e = stoi(x);
		}
		else {
			switch (j) {
			case 0:
				a = x;
				j++;
				break;
			case 1:
				b = x;
				j++;
				break;
			case 2:
				c = x;
				break;
			default:
				break;
			}
		}
		s++;
	}
	if (d < e) {
		ss << d;
		ss << e;
	}
	else {
		ss << e;
		ss << d;
	}
	if (a < b && b < c) {
		first = a;
		second = b;
		Lupin = c;
	}
	else if (a < c && c < b) {
		first = a;
		second = c;
		Lupin = b;
	}
	else if (b < a && a < c) {
		first = b;
		second = a;
		Lupin = c;
	}
	else if (b < c && c < a) {
		first = b;
		second = c;
		Lupin = a;
	}
	else if (c < a && a < b) {
		first = c;
		second = a;
		Lupin = b;
	}
	else if (c < b && b < a) {
		first = c;
		second = b;
		Lupin = a;
	}
	ss << first << second << Lupin;
	cout << ss.str();
}