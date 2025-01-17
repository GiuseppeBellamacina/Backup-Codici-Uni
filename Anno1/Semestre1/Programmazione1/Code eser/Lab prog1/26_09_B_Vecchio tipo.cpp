#include <iostream>
#include <cstdlib>
#include <string>
#include <typeinfo>

#define DIM 50

using namespace std;

class A {
private:
	char* s;
	short len;

protected:
	char get(short i) {
		return s[i % len];
	}

public:
	A(short m) { //costruttore di A
		this->len = m;
		s = new char[len];
		for (int i = 0; i < len; i++) {
			s[i] = (char)(rand() % ((int)'z' - (int)'a' + 1) + (int)'a');
		}
	}

	virtual double elab(short a) = 0; //funzione virtuale pura

	short getLen() { return len; }

	friend ostream& operator<< (ostream& s, A*);
};

class B : public A{
private:
	int p;

protected:
	bool test() {
		for (int i = 0; i < 4; i++) {
			switch (get(i)) {
			case 'a':
			case 'e':
			case 'i':
			case 'o':
			case 'u':
				return true;
			}
		}
		return false;
	}

public:
	B(short m, int x) : A(m) { //costruttore di B
		this->p = x;
	}

	double elab(short a) {
		int V = 0;
		for (int i = 0; i < getLen(); i++) {
			switch (get(i)) {
			case 'a':
			case 'e':
			case 'i':
			case 'o':
			case 'u':
				V++;
			}
		}
		int C = getLen() - V;
		double ret = (double)V / ++C;
		return ret;
	}

	B operator ++ (int) { //overloanding op++ postfisso
		B aux = *this;
		p++;
		return aux;
	}

	friend ostream& operator<< (ostream& s, A*);
};

class C : public A {
private:
	char x;

public:
	C(short n, char c) : A(n) { //costruttore di C
		this->x = c;
	}

	double elab(short r) {
		int num = 0;
		for (int i = (r % getLen()); i < getLen(); i++) {
			if ((int)get(i) >= (int)x)
				num++;
		}
		double avg = (double)num / getLen();
		return avg;
	}

	string g(char c) {
		string ret = "";
		ret += x;
		ret += c;
		return ret;
	}

	friend ostream& operator<< (ostream& s, A*);
};

ostream& operator<<(ostream& s, A* x) { //overloading op<<
	string str = "";
	for (int i = 0; i < x->getLen(); i++) {
		str += x->s[i];
	}
	if (typeid(*x) == typeid(B)) {
		s << ")" << typeid(*x).name() << ", s= " << str << ", p=" << ((B*)x)->p << ", elab(3) = " << x->elab(3) << endl;
	}
	else if (typeid(*x) == typeid(C)) {
		s << ")" << typeid(*x).name() << ", s= " << str << ", x=" << ((C*)x)->x << ", elab(3) = " << x->elab(3) << endl;
	}
	else {
		s << "--ERRORE--" << endl;
	}
	return s;
}

int main() {
	srand(111222333);

	A** vett = new A * [DIM];

	for (int i = 0; i < DIM; i++) {
		short n = 1 + rand() % 10;
		if (rand() % 2 == 0)
			vett[i] = new B(n, rand() % 10 + 1);
		else
			vett[i] = new C(n, (char)(rand() % ((int)'z' - (int)'a' + 1) + (int)'a'));
	}

	cout << "Es. 1" << endl;
	for (int i = 0; i < DIM; i++) {
		cout << i << vett[i];
	}

	cout << endl << "Es. 2" << endl;
	double sum = 0;
	string conc = "";
	for (int i = 0; i < DIM; i++) {
		sum += vett[i]->elab(3);
		if (typeid(*vett[i]) == typeid(C)) {
			string m = ((C*)vett[i])->g('h');
			conc += m;
		}
	}
	cout << "Media: " << sum / DIM << endl;
	cout << "Concatenazione: " << conc << endl;

	cout << endl << "Es. 3" << endl;
	for (int i = 0; i < DIM; i++) {
		if (typeid(*vett[i]) == typeid(B)) {
			cout << "vett[" << i << "] pre-incremento\n" << i << vett[i] << endl;
			//vett[i]++; //RISOLVERE PROBLEMA
			cout << "vett[" << i << "] post-incremento\n" << i << vett[i] << endl;
		}
	}
}