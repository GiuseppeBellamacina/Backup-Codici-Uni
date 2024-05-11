#include <iostream>
#include <cstdlib>
#include <string>
#include <typeinfo>

#define DIM 30

using namespace std;

class A {
	protected:
		double* ptr;
		short len;

	public:
		A(short n) : len(n) { //costruttore di A
			ptr = new double[n];
			for (int i = 0; i < n; i++) {
				ptr[i] = rand() / (double) RAND_MAX;
			}
		}

		virtual double foo(short a) const = 0; //funzione virtual

		//friend ostream& operator<<(ostream& s, A* x);

		virtual ostream& print(ostream& s) {
			string str = "";
			for (int i = 0; i < len; i++) {
				str += to_string(ptr[i]); //#include <string>
				str += " ";
			}
			s << ")" << typeid(*this).name() << ", ptr= [" << str << "]";
			return s;
		}
};

class B : public A {
	private:
		double alpha;

		double extract(short s) const{
			return (ptr[s % len] + alpha) / 2; //ho accesso a ptr perchè è protected
		}

	public:
		B(short m, double d) : alpha(d), A(m) {}; //costruttore di B

		double foo(short b) const {
			return log(1 + extract(b));
		}

		ostream& print(ostream& s) {
			A::print(s);
			s << ", alpha = " << alpha << ", foo(5) = " << foo(5) << endl;
			return s;
		}

		//friend ostream& operator<<(ostream& s, A* x);
};

template <typename T>
class C : public A {
	private:
		T x;

	public:
		C(short n) : A(n) {
			if (typeid(x) == typeid(short)) {
				x = g(n);
			}
			else {
				x = log(1 + n);
			}
		}

		double foo(short r) const {
			return g(r * x);
		}

		T g(T k) const {
			return 3 * k;
		}

		ostream& print(ostream& s) {
			A::print(s);
			s << ", x = " << x << ", foo(5) = " << foo(5) <<", g(5) = "<< g(5) << endl;
			return s;
		}

		//friend ostream& operator<<(ostream& s, A* x);
};

ostream& operator<<(ostream& os, A& x) {
	return x.print(os);
	//string str = "";
	//for (int i = 0; i < x->len; i++) {
	//	str += to_string(x->ptr[i]); //#include <string>
	//	str += " ";
	//}
	//if (typeid(*x) == typeid(B)) {
	//	s << ")" << typeid(*x).name() << ", ptr= [" << str << "], alpha=" << ((B*)x)->alpha<< ", foo(5) = " << x->foo(5) << endl;
	//}
	//else if (typeid(*x) == typeid(C<short>)) {
	//	s << ")" << typeid(*x).name() << ", ptr= [" << str << "], x=" << ((C<short>*)x)->x << ", foo(5) = " << x->foo(5) <<", g(5)= "<< ((C<short>*)x)->g(5) << endl;
	//}
	//else if (typeid(*x) == typeid(C<double>)) {
	//	s << ")" << typeid(*x).name() << ", ptr= [" << str << "], x=" << ((C<double>*)x)->x << ", foo(5) = " << x->foo(5) << ", g(5)= " << ((C<short>*)x)->g(5) << endl;
	//}
	//else {
	//	s << "--ERRORE--" << endl;
	//}
	//return s;
}

int main() {
	srand(328832748);
	A** vett = new A * [DIM];
	for (int i = 0; i < DIM; i++) {
		short n = 1 + rand() % 5;
		switch (rand() % 3) {
		case 0: vett[i] = new B(n, n / 100.0); break;
		case 1: vett[i] = new C<double>(n); break;
		case 2: vett[i] = new C<short>(n);
		}
	}

	cout << "Es. 1" << endl;
	for (int i = 0; i < DIM; i++) {
		cout << i + 1 << *vett[i];
	}
}
