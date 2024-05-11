#include <iostream>
#include <cstdlib>
#include <ctime>
#define DIM 10

using namespace std;

class A{
	public:
		virtual void foo();
};

void A::foo(){
	cout<<"A::foo()"<<endl;
}

class B: public A{
	public:
		void foo(){
			cout<<"B::foo()"<<endl;
		}
};

class C: public A{
	public:
		void foo(){
			cout<<"C::foo()"<<endl;
		}
		
		void boo(){
			cout<<"C::boo()"<<endl;
		}
};

int main(){
	
	srand(time(0));
	
	A** ptr = new A*[DIM];
	
	for(int i = 0; i<DIM; i++){
		if(rand()%2)
			ptr[i]= new B();
		else
			ptr[i] = new C();
	}
	
	for(int i = 0; i<DIM; i++)
		ptr[i] -> foo();
		
	cout<<endl;
	
	C* ptr_c;	
	for(int i = 0; i<DIM; i++){
		ptr_c = dynamic_cast<C*>(ptr[i]);
		if(ptr_c != NULL)
			ptr_c -> boo();
	}
}
