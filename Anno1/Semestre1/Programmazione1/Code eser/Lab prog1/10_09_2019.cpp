#include <iostream>
#include <cstdlib>
#include <string>
#include <typeinfo>
#include <cmath>

#define DIM 50

using namespace std;

class A{
	private:
		double* arr;
		short len;
	
	protected:
		double get(short i){
			return arr[i % len];
		}
	
	public:
		A(short m) : len(m){
			arr = new double [len];
			for(int i = 0; i < len; i++){
				arr[i] = (double) rand() / RAND_MAX;
			}
		}
		
		virtual double f(short a) = 0;
		
		virtual ostream& print(ostream& os){
			os << ")" << typeid(*this).name() << ", arr=[ ";
			for(int i = 0; i < len; i++){
				os << arr[i] << " ";
			}
			return os << "], ";
		}
		
		short getLen(){
			return len;
		}
		
		double operator() (int i1, int i2){
			double sum = 0;
			for(int i = i1; i <= i2; i++){
				sum += arr[i];
			}
			return sum;
		}
};

class B : public A{
	private:
		double p;
	
	protected:
		double foo(short s, int k){
			double sum = 0;
			for(int i = s % getLen(); i < getLen(); i++){
				sum += get(i);
			}
			return sum * k;
		}
	
	public:
		B(short m) : A(m){
			double sum = 0;
			for(int i = 0; i < getLen(); i++){
				sum += get(i);
			}
			p = sum / getLen();	
		}
		
		double f(short a){
			return log(foo(a, 2*a))/p;
		}
		
		ostream& print(ostream& os){
			return A::print(os) << "p=" << p << ", f(3)=" << f(3) << endl;
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
		
		double f(short r){
			return g(r);
		}
		
		T g(T k){
			return 2*x*(k+1);
		}
		
		ostream& print(ostream& os){
			return A::print(os) << "x=" << x << ", f(3)=" << f(3) << endl;
		}
};

ostream& operator<< (ostream& os, A& a){
	return a.print(os);
}

int main(){
	srand(111222333);
	A* vett[DIM];
	for(int i=0; i<DIM; i++){
		short n=1+rand()%10;
		switch(rand()%3) {
	  		case 0: 
	   			vett[i] = new B(n);
	   			break;
  			case 1:
    			vett[i] = new C<double>(n);
    			break;
  			case 2: 
    			vett[i] = new C<short>(n);
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
    for(int i = 1; i < DIM; i++){
    	if(max < vett[i]->f(3))
    		max = vett[i]->f(3);
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
    cout << 10 << *vett[10];
    cout << "(*vett[10])(0, 0)=" << (*vett[10])(0, 0);
}
