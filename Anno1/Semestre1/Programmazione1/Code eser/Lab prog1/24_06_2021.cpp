#include <iostream>
#include <cstdlib>
#include <typeinfo>
#include <string>
#include <cmath>

#define DIM 50

using namespace std;

class A{
	private:
		double* vec;
		short len;
	
	public:
		A(short w, double a, double b) : len(w){ //costruttore di A
			vec = new double[w];
			for(int i = 0; i < w; i++)
				vec[i] = ((double)rand() / RAND_MAX) * (b - a + 1) + a;
		}
		
		virtual double foo(short a) = 0;
		
		virtual ostream& print(ostream& os){
			os << ") " << typeid(*this).name() << ", vec=[";
			for(int i = 0; i < len; i++){
				os << vec[i] << " ";
			}
			return os;
		}
		
		double& operator[](int i){
			return vec[i % len];
		}
		
		short getLen(){
			return len;
		}
	
	protected:
		double get(short i){
			return vec[i % len];
		}	
};

class B : public A{
	private:
		int p;
		
	public:
		B(short m, short x, short y) : A(m, x, y){ //costruttore di B
			p = rand() % (100*y - 10*x + 1) + 10*x;
		}
		
		double foo(short a){
			return log(prod(a, a/2.0));
		}
		
		ostream& print(ostream& os){
			return A::print(os) << "] , p=" << p << " foo(3)=" << foo(3) << endl;
		}
		
	protected:
		double prod(short s, double v){
			double sum = 0;
			for(int i = s % getLen(); i < getLen(); i++)
				sum += get(i);
			return v * sum;
		}
};

template <typename T>
class C : public A{
	private:
		T y;
		
	public:
		C(short n, double x, double y) : A(n, x, y){ //costruttore di C
			if(typeid(T) == typeid(short))
				this->y = n;
			else
				this->y = 1 + cos(n)*cos(n);
		}
		
		double foo(short r){
			return g(r);
		}
		
		double g(double k){
			return 2.0 * y * (k+1);
		}
		
		ostream& print(ostream& os){
			return A::print(os) << "] , y=" << y << " foo(3)=" << foo(3) << endl;
		}
};

ostream& operator<< (ostream& os, A& a){
	return a.print(os);
}

int main(){
	srand(111222333);
	
	//A** vett = new A*[DIM];
	A* vett[DIM];

    for(int i=0; i<DIM; i++) {
		short n=5+rand()%5;
		switch(rand()%3) {
	  		case 0: 
	    		vett[i]= new B(n, rand()%5 + 1, rand()%10 + 5);
	    		break;
	  		case 1:
	    		vett[i]= new C<double>(n, rand()%5 + 1, rand()%10 + 5);
	    		break;
	  		case 2: 
	    		vett[i]= new C<short>(n, rand()%5 + 1, rand()%10 + 5);
		}
    }
    
    //PUNTO 1
    cout << "PUNTO 1:" << endl;
    for(int i = 0; i < DIM; i++)
    	cout << i << *vett[i];
    cout << endl;
    
    //PUNTO 2
    cout << "PUNTO 2:" << endl;
    double max = vett[0]->foo(3);
    for(int i = 1; i < DIM; i++){
    	if(vett[i]->foo(3) > max)
    		max = vett[i]->foo(3);
	}
	double sum = 0;
	short counter = 0;
	for(int i = 0; i < DIM; i++){
		if(typeid(*vett[i]) == typeid(C<double>)){
			sum += ((C<double>*)vett[i])->g(0.5);
			counter++;
		}
	}
	double media = sum / counter;
	
	cout << "Max: " << max << endl;
	cout << "Media: " << media << endl;
	cout << endl;
	
	
	//PUNTO 3
    cout << "PUNTO 3:" << endl;
    cout << 10 << *vett[10] << endl;
    cout << "(*vett[10])[0] = " << (*vett[10])[0] << endl;
    (*vett[10])[0] = 4.5;
    cout << "(*vett[10])[0] = " << (*vett[10])[0] << endl;
}
