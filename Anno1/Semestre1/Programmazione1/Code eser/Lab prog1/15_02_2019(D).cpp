#include <iostream>
#include <cstdlib>
#include <cmath>
#include <typeinfo>
#include <string>

#define DIM 50

using namespace std;

class A{
	private:
		int* ptr;
		short len;
	
	public:
		A(short m, short k) : len(m){
			ptr = new int [len];
			for(int i = 0; i < len; i++){
				ptr[i] = 1 + rand() % k;
			}
		}
		
		virtual double const f() = 0;
		
		virtual ostream& print(ostream& os){
			os << ")" << typeid(*this).name() << ", ptr=[ ";
			for(int i = 0; i < len; i++){
				os << ptr[i] << " ";
			}
			return os << "], ";
		}
		
		int get(short i){
			return ptr[i % len];
		}
		
		short getLen(){
			return len;
		}
		
		int& operator[] (short i){
			return ptr[i % len];
		}
};

class B : public A{
	private:
		double p;
	
	public:
		B(short m, short k, double y) : A(m, k), p(y){}
		
		double const f(){
			double sum = 0;
			for(int i = 0; i < getLen(); i++){
				if(get(i) % 2 == 0)
					sum += get(i);
			}
			return sum / p;
		}
		
		ostream& print(ostream& os){
			return A::print(os) << "p=" << p << ", f()=" << f() << endl;
		}
};

class C : public A{
	private:
		char x;
	
	public:
		C(short n, short k, char c) : A(n, k), x(c){}
		
		double const f(){
			int counter = 0;
			double sum = 0;
			for(int i = 0; i < getLen(); i++){
				if(get(i) % 2){
					sum += get(i);
					counter++;
				}
			}
			if(counter)
				return sum / counter;
			else
				return 0;
		}
		
		string const g(char c){
			string s = "";
			s += x;
			s += c;
			return s;
		}
		
		ostream& print(ostream& os){
			return A::print(os) << "x=" << x << ", f()=" << f() << endl;
		}
};

ostream& operator<< (ostream& os, A& a){
	return a.print(os);
}

int main(){
	srand(111222333);
    A *vett[DIM];
    for(int i=0; i<DIM; i++){
		short n=1+rand()%10;
		short m = 1+rand()%8;
		if(rand()%2==0)
	  		vett[i]= new B(n, m, rand()/(double) RAND_MAX+0.05);
		else
	  		vett[i]= new C(n, m, (char) (rand()%('z' - 'a' + 1) + 'a'));
    }
    
    //PUNTO 1
    cout << "PUNTO 1" << endl;
    for(int i = 0; i < DIM; i++){
    	cout << i << *vett[i];
	}
	cout << endl;
	
	//PUNTO 2
    cout << "PUNTO 2" << endl;
    double sum = 0;
    string s = "";
    for(int i = 0; i < DIM; i++){
    	sum += vett[i]->f();
    	if(typeid(*vett[i]) == typeid(C)){
    		s += ((C*)vett[i])->g('h');
		}
	}
	cout << "Media: " << sum / DIM << endl;
	cout << "Concatenazione: " << s << endl;
    cout << endl;
    
    //PUNTO 3
    cout << "PUNTO 3" << endl;
    cout << 9 << *vett[9];
    cout << "(*vett[9])[0] = 445" << endl;
    (*vett[9])[0] = 445;
    cout << 9 << *vett[9];
}
