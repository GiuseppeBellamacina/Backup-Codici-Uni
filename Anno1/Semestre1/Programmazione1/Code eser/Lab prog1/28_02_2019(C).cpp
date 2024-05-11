#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include <typeinfo>

#define DIM 50

using namespace std;

class A{
	private:
		char* base;
		short len;
	
	protected:
		char get(short i){
			return base[i % len];
		}
	
	public:
		A(short m) : len(m){
			base = new char [len];
			for(int i = 0; i < len; i++)
				base[i] = (char)('a'+ rand() % ('z' - 'a' + 1));
		}
		
		virtual string extract(short x) = 0;
		
		virtual ostream& print(ostream& os){
			os << ")" << typeid(*this).name() << ": base=[ ";
			for(int i = 0; i < len; i++)
				os << base[i] << " ";
			return os << "], ";
		}
		
		short getLen(){
			return len;
		}
};

class B : public A{
	private:
		string str;
		double k;
	
	public:
		B(short m, double p) : A(m), k(p){
			for(int i = 0; i < getLen(); i++){
				switch(get(i)){
					case 'a':
					case 'e':
					case 'i':
					case 'o':
					case 'u':
						str += get(i);
				}
			}
		}
		
		double foo(short s){
			return sin(k+s)/log(s+1);
		}
		
		string extract(short x){
			string s = "";
			for(int i = 0; i < x; i++){
				s += get(rand() % getLen());
			}
			return s;
		}
		
		ostream& print(ostream& os){
			return A::print(os) << "str=" << str << ", k=" << k << ", extact(3)=" << extract(3) << endl;
		}
};

class C : public A{
	private:
		int y;
	
	public:
		C(short n, int k) : A(n), y(k) {}
		
		double g(short w){
			return sin(w+y);
		}
		
		string extract(short x){
			string s = "";
			for(int i = 0; i < getLen(); i++){
				switch(get(i)){
					case 'a':
					case 'e':
					case 'i':
					case 'o':
					case 'u':
						break;
					default:
						s += get(i);
				}
			}
			if(s.length() <= x)
				return s;
			else
				return s.substr(0, x);
		}
		
		ostream& print(ostream& os){
			return A::print(os) << "y=" << y << ", extact(3)=" << extract(3) << endl;
		}
		
		C operator++(int){
			C aux = *this;
			y++;
			return aux;
		}
};

ostream& operator<<(ostream& os, A& a){
	return a.print(os);
}

int main(){
	A *vett[DIM];
	srand(111222333);
    for(int i=0; i<DIM; i++){
		short n=10+rand()%10;
		switch(rand()%2){
	  		case 0:
	    		vett[i]= new C(n, rand()%20 + 1);
	    		break;
	  		case 1:
	    		vett[i]= new B(n, rand()/(double) RAND_MAX);
	    		break;
		}
    }
    
    //PUNTO 1
    cout << "PUNTO 1" << endl;
    for(int i = 0; i < DIM; i++)
    	cout << i << *vett[i];
    cout << endl;
    
    //PUNTO 2
    cout << "PUNTO 2" << endl;
    double sumB = 0, sumC = 0;
    int c1 = 0, c2 = 0;
    for(int i = 0; i < DIM; i++){
    	if(typeid(*vett[i]) == typeid(B)){
    		sumB += ((B*)vett[i])->foo(5);
    		c1++;
    	}
    	else{
    		sumC += ((C*)vett[i])->g(5);
    		c2++;
    	}
	}
	sumB/=c1;
	sumC/=c2;
	cout << "Avg(g() + foo())=" << (sumB + sumC) / 2 << endl;
    cout << endl;
    
    //PUNTO 3
    cout << "PUNTO 3" << endl;
    cout << 0 << *vett[0];
    (*((C*)vett[0]))++;
    cout << 0 << *vett[0];
}
