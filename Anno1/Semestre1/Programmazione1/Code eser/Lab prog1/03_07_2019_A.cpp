#include <iostream>
#include <cstdlib>
#include <string>
#include <typeinfo>

#define DIM 50

using namespace std;

class A{
	private:
		int* arr;
		short len;
	
	protected:
		double get(short i){
			return arr[i % len];
		}
	
	public:
		A(short m, int a, int b) : len(m){
			arr = new int [len];
			for(int i = 0; i < len; i++){
				arr[i] = a + rand() % (b - a + 1);
			}
		}
		
		virtual double func (short i) = 0;
		
		virtual ostream& print(ostream& os){
			os << ")" << typeid(*this).name() << ", arr=[ ";
			for(int i = 0; i < len; i++)
				os << arr[i] << " ";
			return os << "], ";
		}
		
		short getLen(){
			return len;
		}
		
		int& operator[] (int i){
			return arr[i % len];
		}
};

class B : public A{
	private:
		double p;
	
	public:
		B(short m, int y, int z, double x) : A(m, y, z), p(x) {}
		
		double func(short i){
			double min = get(0), max = get(0);
			for(int i = 1; i < getLen(); i++){
				if(min > get(i))
					min = get(i);
				if(max < get(i))
					max = get(i);
			}
			return min / max + p;
		}
		
		ostream& print(ostream& os){
			return A::print(os) << "p=" << p << ", func(3)=" << func(3) << endl;
		}
};

class C : public A{
	private:
		char t;
	
	public:
		C(short n, char c, int a, int b) : A(n, a, b), t(c) {}
		
		double func(short i){
			double sum = 0;
			for(int i = 0; i < getLen(); i++){
				sum += get(i);
			}
			return sum / getLen();
		}
		
		string g(char c, short k){
			string s = "";
			for(int i = 0; i < k; i++){
				s += t;
				s += c;
			}
			return s;
		}
		
		ostream& print(ostream& os){
			return A::print(os) << "t=" << t << ", func(3)=" << func(3) << endl;
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
		if(rand()%2==0)
			vett[i]= new B(n, rand()%5+1, rand()%11+10, (double) rand()/(RAND_MAX));
		else
			vett[i]= new C(n, (char) (rand()%('z' - 'a' + 1) + 'a'), rand()%5+1, rand()%11+10);
    }
    
    //PUNTO 1
    cout << "PUNTO 1" << endl;
    for(int i = 0; i < DIM; i++){
    	cout << i << *vett[i];
	}
	cout << endl;
	
	//PUNTO 2
	cout << "PUNTO 2" << endl;
	int counter = 3;
	double sum = 0;
	for(int i = 0; i < DIM; i++){
		sum += vett[i]->func(3);
	}
	cout << "Media: " << sum / DIM << endl;
	for(int i = 0; i < DIM && counter > 0; i++){
		if(typeid(*vett[i]) == typeid(C)){
			cout << "i=" << i << ", g('h', 2)=" << ((C*)vett[i])->g('h', 2) << endl;
			counter--;
		}
	}
	cout << endl;
	
	//PUNTO 3
	cout << "PUNTO 3" << endl;
	cout << 0 << *vett[0];
	cout << "(*vett[0])[0] = 118" << endl;
	(*vett[0])[0] = 118;
	cout << 0 << *vett[0];
}
