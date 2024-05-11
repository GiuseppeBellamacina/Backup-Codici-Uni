#include <iostream>
#include <string>
#include <typeinfo>
#include <cstdlib>
#include <cmath>

#define DIM 50

using namespace std;

class A{
	private:
		short* arr;
		short len;
		
	protected:
		short get(short i){
			return arr[i % len];
		}
		
	public:
		A(short m) : len(m){
			arr = new short [len];
			for(int i = 0; i < len; i++)
				arr[i] = (short) rand() % 10 + 1;
		}
		
		virtual double f(short a) = 0;
		
		virtual ostream& print(ostream& os){
			os << ")" << typeid(*this).name() << ", arr=[ ";
			for(int i = 0; i < len; i++)
				os << arr[i] << " ";
			return os << "], ";
		}
		
		short getLen(){
			return len;
		}
};

template <typename T>
class B : public A{
	private:
		T x;
	
	public:
		B(short m, char c) : A(m){
			if(typeid(T) == typeid(char))
				x = c;
			else{
				for(int i = 0; i < m; i++)
				x += c;
			}
		}
		
		double foo(short s){
			return log(s) + sin(f(s));
		}
		
		double f(short a){
			double sum = 0;
			short counter = 0;
			for(int i = a % getLen(); i < getLen(); i++){
				sum += get(i);
				counter++;
			}
			return sum / counter;
		}
		
		ostream& print(ostream& os){
			return A::print(os) << "x=" << x << ", f(3)=" << f(3) << endl;
		}
};

class C : public A{
	private:
		int y;
	
	public:
		C(short n, int k) : A(n), y(k) {}
		
		double f(short a){
			short r = get(rand() % getLen());
			return (double) (a+y) / r;
		}
		
		double g(short w){		//il tipo di ritorno che ci vuole è double, non short
			return sin(w+y);	//Messina è babbo
		}
		
		ostream& print(ostream& os){
			return A::print(os) << "y=" << y << ", f(3)=" << f(3) << endl;
		}
		
		C& operator++(){
			y++;
			return *this;
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
	    		vett[i]= new C(n, rand()%10 + 1);
	    		break;
	  		case 1:
	    		vett[i]= new B<string>(n, rand()%('z' - 'a' + 1) + 'a');
	    		break;
	  		case 2: 
	    		vett[i]= new B<char>(n, rand()%('z' - 'a' + 1) + 'a');
		}
    }
    
    //PUNTO 1
    cout << "PUNTO 1" << endl;
    for(int i = 0; i < DIM; i++)
    	cout << i << *vett[i];
    cout << endl;
    	
    //PUNTO 2
    cout << "PUNTO 2" << endl;
    double max = vett[0]->f(3);
    double sum = 0;
    short c = 0;
    for(int i = 0; i < DIM; i++){
    	if(max < vett[i]->f(3)){
    		max = vett[i]->f(3);
		}
		if(typeid(*vett[i]) == typeid(C)){
			sum += ((C*)vett[i])->g(5);
			c++;
		}
	}
	cout << "Max: " << max << endl;
	cout << "Avg: " << sum / c;
	cout << endl << endl;
	
	//PUNTO 3
	cout << "PUNTO 3" << endl;
	cout << 3 << *vett[3];
	++(*((C*)vett[3]));
	cout << 3 << *vett[3];
}
