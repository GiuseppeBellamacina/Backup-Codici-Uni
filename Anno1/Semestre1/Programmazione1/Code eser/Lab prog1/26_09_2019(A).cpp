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
		char get(short i){
			return str[i % len];
		}
	
	public:
		A(short m, string source) : len(m){
			str = new char[len];
            string cons = "";
            int count = 0;
            for(int i = 0; i < source.length(); i++) {
                switch(toupper(source[i])) {
                    case 'A':
                    case 'E':
                    case 'I':
                    case 'O':
                    case 'U': {
                        if(count < len) {
                            str[count++] = source[i];
                        }
                        break;
                    }
                    default: {
                        cons += source[i];
                    }
                }
            }
            for(int i = 0; i < cons.length(); i++) {
                if(count < len) {
                    str[count++] = cons[i];
                }
            }
		}
		
		virtual string func(short k) = 0;
		
		virtual ostream& print(ostream& os){
			string s = "";
            for(int i = 0; i < len; i++)
				s += str[i];
            os << typeid(*this).name() << ", str = " << s << ", ";
            return os;
		}
		
		string operator() (int i1, int i2) {
            string s = "";
            for(int i = i1; i <= i2; i++) {
                s += str[i];
            }
            return s;
        }
		
		short getLen(){
			return len;
		}
};

class B : public A{
	private:
		short q;
	
	public:
		B(short m, string source) : A(m, source){
			q = 1 + (rand() % getLen());
		}
		
		string func(short k){
			string inv = "";
			for(int i = getLen() - 1; i >= getLen() - k; i--){
				inv += get(i);
			}
			return inv;
		}
		
		ostream& print(ostream& os){
            return A::print(os) << "q=" << q << ", func(3)=" << func(3);
		}
};

class C : public A{
	private:
		char y;
	
	public:
		C(short n, string source, char y) : A(n, source), y(y){}
		
		string func(short k){
			string inv = "";
            for(int i = getLen() - 1; i >= k; i--) {
                inv += get(i);
            }
            return inv;
		}
		
		string g(char c){
			string s = "";
			for(int i = 0; i < getLen(); i++){
				s += get(i);
			}
			return y + s + c;
		}
		
		ostream& print(ostream& os){
            return A::print(os) << "y=" << y << ", func(3)=" << func(3);
		}
};

ostream& operator<< (ostream& os, A& a){
	return a.print(os);
}

int main() {
    srand(111222333);
    string S;
    A* vett[DIM];
    short fa = 3; //???

    for (int i = 0; i < DIM; i++) {
        short n = 10 + rand() % 10;
        S = "";
        for (int k = 0; k < 20; k++)
            S += rand() % ('z' - 'a' + 1) + 'a';
        if (rand() % 2 == 0)
            vett[i] = new B(n, S);
        else
            vett[i] = new C(n, S, (char)(rand() % ('z' - 'a' + 1) + 'a'));
    }

    //PUNTO 1
    cout << "PUNTO 1" << endl;
    for(int i = 0; i < DIM; i++) {
        cout << i << ") " << *vett[i] << endl;
    }

    //PUNTO 2
    cout << endl << "PUNTO 2" << endl;
    for(int i = DIM - 1; i >= 0; i--) {
        if(typeid(*vett[i]) == typeid(C)) {
            cout << "j = " << i << ", g('X') = " << ((C*)vett[i])->g('X') << endl;
            break;
        }
    }

    //PUNTO 3
    cout << endl << "PUNTO 3" << endl;
    cout << "*vett[5] = " << *vett[5] << endl;
    cout << "vett[5](1, 3) = " << (*vett[5])(1, 3) << endl;
}
