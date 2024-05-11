#include <iostream>
#include <cstdlib>
#include <cmath>
#include <typeinfo>

#define DIM 50

using namespace std;

class A{
	private:
		double* w;
		short len;
	
	protected:
		double const get(short i){
			return w[i % len];
		}
	
	public:
		A(short m) : len(m){
			w = new double [len];
			for(int i = 0; i < len; i++){
				w[i] = (double)rand() / RAND_MAX;
			}
		}
		
		virtual double const foo(short a) = 0;
		
		virtual ostream& print(ostream& os){
			os << ")" << typeid(*this).name() << ", w=[ ";
			for(int i = 0; i < len; i++){
				os << w[i] << " ";
			}
			return os << "], ";
		}
		
		short const getLen(){
			return len;
		}
		
		double& operator[] (int i){
			return w[i % len];
		}
};

class B : public A{
	private:
		int p;
	
	protected:
		double const sum(short s){
			double sum = 0;
			for(int i = s % getLen(); i < getLen(); i++){
				sum += get(i);
			}
			return sum;
		}
		
	public:
		B(short m, int x) : A(m), p(x) {}
		
		double const foo(short a){
			return sum(a) / p;
		}
		
		ostream& print(ostream& os){
			return A::print(os) << "p=" << p << ", foo(3)=" << foo(3) << endl;
		}
};

template <typename T>
class C : public A{
	private:
		T x;
	
	public:
		C(short n) : A(n){
			if(typeid(T) == typeid(short))
				x = n;
			else
				x = log(1 + pow(sin(n), 2));
		}
		
		double const foo(short r){
			return g(r);
		}
		
		T const g(T k){
			return 2*x*(k+1);
		}
		
		ostream& print(ostream& os){
			return A::print(os) << "x=" << x << ", foo(3)=" << foo(3) << endl;
		}
};

ostream& operator<< (ostream& os, A& a){
	return a.print(os);
}

int main(){
    srand(111222333);
    A *vett[DIM];
    for(int i=0; i<DIM; i++) {
		short n=1+rand()%10;
		switch(rand()%3) {
	  		case 0: 
	    		vett[i]= new B(n, rand()%10 + 1);
	    		break;
	  		case 1:
	    		vett[i]= new C<double>(n);
	    		break;
	  		case 2: 
	    		vett[i]= new C<short>(n);
		}
    }
	
	//PUNTO 1
	cout << "PUNTO 1" << endl;
	for(int i = 0; i < DIM; i++){
		cout << i << *vett[i];
	}
	cout << endl;
	
	//PUNTO 2
    cout << "PUNTO 2" << endl;
    double max = vett[0]->foo(3);
    for(int i = 1; i < DIM; i++){
    	if(max < vett[i]->foo(3))
    		max = vett[i]->foo(3);
	}
	cout << "Max: " << max << endl;
	double sum = 0;
	short counter = 0;
	for(int i = 0; i < DIM; i++){
		if(typeid(*vett[i]) == typeid(C<double>)){
			sum += static_cast<C<double>*>(vett[i])->g(5);
			counter++;
		}
	}
	cout << "Media: " << sum / counter << endl;
	cout << endl;
	
	//PUNTO 3
	cout << "PUNTO 3" << endl;
	cout << 4 << *vett[4];
	cout << "(*vett[10])[2] = 3.1415" << endl;
	(*vett[4])[1] = 3.1415;
	cout << 4 << *vett[4];
}
