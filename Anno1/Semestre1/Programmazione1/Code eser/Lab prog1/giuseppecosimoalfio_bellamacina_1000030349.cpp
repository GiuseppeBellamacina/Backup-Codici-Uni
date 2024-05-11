//BELLAMACINA GIUSEPPE COSIMO ALFIO
//1000030349

#include <iostream>
#include <cstdlib>
#include <string>
#include <typeinfo>

#define DIM 50

using namespace std;

class A{
	private:
		char* str;
		short len;
	
	protected:
		string extract(short k){
			string s = "";
			for(int i = 0; i < len; i++)
				s += str[i];
			if(k >= len)
				return s;
			else
				return s.substr(len - k, k);
		}
	
	public:
		A(short w, char c1, char c2) : len(w){
			str = new char [len];
			for(int i = 0; i < len; i++)
				str[i] = (char) (c1 + rand() % (c2 - c1 + 1));
		}
		
		virtual short f(short k) = 0;
		
		virtual ostream& print(ostream& os){
			string s = "";
            for(int i = 0; i < len; i++)
				s += str[i];
            os << ")" << typeid(*this).name() << " str=" << s << ", ";
            return os;
		}
		
		string operator() (int i1, int i2) {
            string s = "";
            for(int i = i1; i <= i2; i++) {
                s += str[i];
            }
            return s;
        }
};

class B : public A{
	private:
		char z;
	
	public:
		B(short m, char c1, char c2) : A(m, c1, c2){
			string s = extract(m/2+1);
			z = s[rand() % s.length()];
		}
		
		short f(short k){
			short counter = 0;
			string s = extract(k);
			for(int i = 0; i < s.length(); i++){
				if(s[i] <= z)
					counter++;
			}
			return counter;
		}
		
		ostream& print(ostream& os){
            return A::print(os) << "z=" << z << endl;
		}
};

template <typename T>
class C : public A{
	private:
		T ss;
	
	public:
		C(short w, char c1, char c2) : A(w, c1, c2){
			if(typeid(ss) == typeid(string)){
				string s = extract(w/2+1);
				for(int i = 0; i < s.length(); i++)
					ss += s[i];
			}
			else
				ss = w;
		}
		
		short f(short k){
			string s = extract(k);
			for(int i = 0; i < s.length(); i++){
				if(s[i] >= 'A' || s[i] <= 'Z')  //errore &&
					return 1;
			}
			return 0;
		}
		
		T foo(short x){
			T ret;
			for(int i = 0; i < x; i++)
				ret += ss;
			return ret;
		}
		
		ostream& print(ostream& os){
            return A::print(os) << "ss=" << ss << endl;
		}
};

ostream& operator<< (ostream& os, A& a){
	return a.print(os);
}

int main(){
	srand(12345678);
	A* vec[DIM];
	for(unsigned int i=0; i<DIM; i++){
    	int r = rand(); 
    	if(r%3==0) // B 
      		vec[i] = new B(rand()%10+5, '0', '9');
    	else if(r%3==1)
      		vec[i] = new C<string>(rand()%10+5, 'a', 'z');
    	else
      		vec[i] = new C<short>(rand()%20+10, 'A', 'Z');
	}
	
	//PUNTO 1
	cout << "PUNTO 1" << endl;
	for(int i = 0; i < DIM; i++)
		cout << i << *vec[i];
	cout << endl;
	
	//PUNTO 2
	cout << "PUNTO 2" << endl;
	int cf5 = 0, foo3 = 0;
	for(int i = 0; i < DIM; i++){
		if(vec[i]->f(5) >= 4)
			cf5++;
		if(typeid(*vec[i]) == typeid(C<short>))
			foo3 += ((C<short>*)vec[i])->foo(3);
	}
	cout << "NUM f(5)>=4: " << cf5 << endl;
	cout << "NUM foo(3) di C<short>: " << foo3 << endl;
	cout << endl;
	
	//PUNTO 3
	cout << "PUNTO 3" << endl;
	cout << 0 << *vec[0];
    cout << "vec[0](0, 2) = " << (*vec[0])(0, 2) << endl;
}
