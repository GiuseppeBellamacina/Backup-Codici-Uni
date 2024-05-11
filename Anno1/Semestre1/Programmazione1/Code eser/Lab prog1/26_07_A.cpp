#include <iostream>
#include <cstdlib>
#include <ctime>
#include <typeinfo>
#define DIM 50

using namespace std;

class A {
    private:
        char* str;
        short len;

    public:
        A(short m, string source) {
            this->len = m;
            this->str = new char[len];
            for(int i = 0; i < this->len; i++) {
                str[i] = source[rand() % source.length()];
            }
        }

        virtual char func(short i) = 0;

        short getLen() {
            return this->len;
        }

        virtual ostream& print(ostream& os) {
            string s = "";
            for(int i = 0; i < this->len; i++) {
                s += str[i];
            }
            return os << typeid(*this).name() << ", str = " << s;  
        }

        string operator () (int i1, int i2) {
    		string s = "";
    		for(int i = i1; i < i2; i++) {
        		s += A::get(i);
    		}
    		return s;
		} 
    
    protected:
        char get(short i) {
            return str[i % this->len];
        }
};

ostream& operator << (ostream& s, A& a) {
    return a.print(s);
}

class B : public A {
    private:
        short p;
    
    public:
        B(short m, string source) : A(m, source) {
            this->p = 1;
            for(int i = 0; i < m; i++) {
                switch(toupper(A::get(i))) {
                    case 'A':
                    case 'E':
                    case 'I':
                    case 'O':
                    case 'U': {
                        this->p += 1;
                        break;
                    }
                }
            }
        }

        char func(short i) {
            char r = 'X';
            for(int j = i; j < A::getLen() && r == 'X'; j++) {
                switch(toupper(A::get(j))) {
                    case 'A':
                    case 'E':
                    case 'I':
                    case 'O':
                    case 'U': {
                        break;
                    }
                    default: {
                        r = A::get(j);
                    }
                }
            }
            return r;
        }

        ostream& print(ostream& os) {
            return A::print(os) << ", p=" << this->p << ", func(3)=" << this->func(3) << endl;
        }

};

class C : public A {
    private:
        char x;

    public:
        C(short n, string source, char y) : A(n, source) {
            this->x = y;
        }

        char func(short i) {
            for(int j = i; j < A::getLen(); j++) {
                if(A::get(j) > this->x) return A::get(j);
            }
            return this->x;
        }

        string g(char c) {
            string s = "";
            for(int i = 0; i < getLen(); i++) {
                s += get(i);
            }
            return this->x + s + c;
        }

        ostream& print(ostream& os) {
            return A::print(os) << ", x=" << this->x << ", func(3)=" << this->func(3) << endl;
        }
};

int main() {
    srand(111222333);
    A* vett[DIM];

    string S = "supercalifragilistichespiralidoso";

    for (int i = 0; i < DIM; i++) {
    short n = 3 + rand() % 10;
    if (rand() % 2 == 0)
        vett[i] = new B(n, S);
    else
        vett[i] = new C(n, S, (char)(rand() % ('z' - 'a' + 1) + 'a'));
    }

   
    cout << "PUNTO 1" << endl;
    for(int i = 0; i < DIM; i++) {
        cout << i << ")" << *vett[i];
    }

   
    cout << "PUNTO 2" << endl;
    string s = "";
    for(int i = 0; i < DIM; i++) {
        if(typeid(*vett[i]) == typeid(C)) {
            s += ((C*)(vett[i]))->g('h');
        }
    }
    cout << "Concatenazione=" << s << endl;

    
    cout << endl << "PUNTO 3" << endl;
    cout << "*vett[5]=" << *vett[5];
    cout << "vett[5](1, 3)=" << (*vett[5])(1, 3);
}
