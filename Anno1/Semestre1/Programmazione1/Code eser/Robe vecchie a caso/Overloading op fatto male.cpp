#include <iostream>

using namespace std;

class A{

	int a, b, c;
	 
	public:
		A(int x, int y, int z):a(x), b(y), c(z){}
		friend A operator+ (const A sx, const A dx);
		void Stampa(){
			cout<<this->a<<endl<<this->b<<endl<<this->c;
		}
};

A operator+ (const A sx, const A dx){
	return A(sx.a + dx.a, sx.b + dx.b, sx.c + dx.c);
}

int main(){
	A a =A(1, 1, 1);
	A b =A(9, 8, 7);
	A c = a + b;
	c.Stampa();
	
}
