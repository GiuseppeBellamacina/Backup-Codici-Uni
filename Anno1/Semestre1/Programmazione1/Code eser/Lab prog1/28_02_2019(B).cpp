#include <iostream>
#include <cstdlib>
#include <typeinfo>
#include <cmath>
#include <string>

#define DIM 50

using namespace std;

class A{
	private:
		char* ptr;
		short len;
	
	protected:
		char get(short i){
			return ptr[i % len];
		}
	
	public:
		A(short m, char c) : len(m){
			ptr = new char [len];
			for(int i = 0; i < len; i++)
				ptr[i] = (char)((int) 'a' + rand() % ((int) c - (int) 'a' +1));
		}
		
		virtual string elab(short a, char c) = 0;
		
		virtual ostream& print(ostream& os){
			os << ")" << typeid(*this).name() << ", ptr=[ ";
			for(int i = 0; i < len; i++)
				os << ptr[i] << " ";
			return os << "], ";
		}
		
		short getLen(){
			return len;
		}
};

class B : public A{
	private:
		double x;
	
	public:
		B(short m, double y, char c) : A(m, c), x(y) {}
		
		double foo(short s){
			return sin(x+s) / log(x+s);
		}
		
		string elab(short a, char c){
			string s = "";
			for(int i = 0; i < getLen(); i++){
				int dif = abs((int)get(i) - (int)c);
				if(dif <= a)
					s += get(i);
			}
			return s;
		}
		
		ostream& print(ostream& os){
			return A::print(os) << "x=" << x << ", elab(5, 'z')=" << elab(5, 'z') << endl;
		}
};

template <typename T>
class C : public A{
	private:
		T y;
	
	public:
		C(short n, double k, char c) : A(n, c){
			if(typeid(T) == typeid(short))
				y = round(100*k);
			else
				y = k;
		}
		
		string elab(short a, char c){
			string s = "";
			if(getLen() >= a){
				for(int i = 0; i < a; i++)
					s += c;
			}
			else{
				for(int i = 0; i < getLen(); i++)
					s += get(i);
			}
			return s;
		}
		
		double g(short w){
			return sin(w+y);
		}
		
		ostream& print(ostream& os){
			return A::print(os) << "y=" << y << ", elab(5, 'z')=" << elab(5, 'z') << endl;
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
        		vett[i]= new B(n, (double) rand()/RAND_MAX, rand()%('z' - 'a' + 1) + 'a');
				break;
      		case 1:
				vett[i]= new C<double>(n, (double) rand()/RAND_MAX, rand()%('z' - 'a' + 1) + 'a');
				break;
     		case 2:
				vett[i]= new C<short>(n, (double) rand()/RAND_MAX, rand()%('z' - 'a' + 1) + 'a');
      	}
	}
	
	//PUNTO 1
	cout << "PUNTO 1" << endl;
	for(int i = 0; i < DIM; i++)
		cout << i << *vett[i];
	cout << endl;
}
