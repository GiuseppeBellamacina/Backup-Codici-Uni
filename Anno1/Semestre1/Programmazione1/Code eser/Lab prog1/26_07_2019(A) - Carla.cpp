#include <iostream>
#include <cstdlib>
#include <cstring>
#include <typeinfo>
#define DIM 50
using namespace std;

class A{
	private:
		char *str;
		short len;
	public:
		A(short m,string source):len(m){
			this->str=new char[len];
			for(int i=0;i<m;i++)
			str[i]=source[rand()%source.length()];
				}
		virtual char func(short i)=0; //virtuale pura
		
		short getLen(){
			return this->len;
		}
		virtual ostream& put(ostream& os) {
            string s = "";
            for(int i = 0; i < this->len; i++) {
                s += str[i];
            }
            return os << typeid(*this).name() << ", str = " << s;  
        }
	protected:
		char get(short i){
			return this->str[i%this->len];
		}
	
};

 ostream& operator << (ostream& s, A& obj) {
    return obj.put(s);
}

class B:public A{
	private:
		short p;
	public:
		B(short m,string source):A(m,source){
			this->p=1;
			for(int i=0;i<m;i++)
			switch(tolower(get(i))){
				case 'a':
				case 'e':
				case 'i':
				case 'o':
				case 'u': this->p+=1;
				break;
			}
		}
		
		char func(short i){
			char r='X';
			for(int j=i; j<getLen() && r=='X';j++){
				switch(tolower(get(j))){
				case 'a':
				case 'e':
				case 'i':
				case 'o':
				case 'u': {
					break;
				}
				default:{
					r=get(j);
				}
			}
		}
			return r;
		}
		ostream& put(ostream& os) {
            return A::put(os) << ", p=" << this->p << ", func(3)=" << this->func(3) << endl;
        }
};

class C:public A{
	private:
		char x;
	public:
		C(short n,string source,char y):A(n,source){
			this->x=y;
		}
		char func(short i){
			for(int j=i;i<getLen();j++){
				if(get(j)>this->x)
				return get(j);
			}
			return this->x;
		}
		string g(char c){
			string s = "";
            for(int i=0; i < getLen(); i++) {
                s+=get(i);
            }
			return this->x+ s+ c;
		}
		ostream& put(ostream& os) {
            return A::put(os) << ", x=" << this->x << ", func(3)=" << this->func(3) << endl;
        }
};

int main(){
	srand(111222333);
    A* vett[DIM];

    string S = "supercalifragilistichespiralidoso";

    for (int i = 0; i < DIM; i++) {
    short n = 3 + rand() % 10;
    if (rand() % 2 == 0)
        vett[i] = new B(n,S);
    else
        vett[i] = new C(n,S,(char)(rand() % ('z' - 'a' + 1) + 'a'));
    }

//Punto 1
for(int i=0;i<DIM;i++)
cout<<*vett[i]<<endl;

//Punto 2
/*string s = "";
    for(int i = 0; i < DIM; i++) {
        if(typeid(*vett[i]) == typeid(C)) 
            s += ((C*)(vett[i]))->g('h');
        }
    cout << "concat=" << s << endl;*/



}
