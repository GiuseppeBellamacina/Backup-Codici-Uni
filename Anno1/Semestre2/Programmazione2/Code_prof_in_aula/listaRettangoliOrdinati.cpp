
#include <iostream>
using namespace std;

class Rettangolo{
private:
    int b,h;
public:
    Rettangolo(int _b=10, int _h=5): b(_b), h(_h){}
    int getB()const{return b;}
    int getH()const{return h;}

    bool operator>(const Rettangolo& r) const { return (b*h) > (r.b*r.h);}
    bool operator==(const Rettangolo& r) const { return (b==r.b && h == r.h);}
    bool operator!=(const Rettangolo& r) const { return !(b==r.b && h == r.h);}

    friend
    ostream& operator<<(ostream& out, const Rettangolo& r);
};

ostream& operator<<(ostream& out, const Rettangolo& r){
    out <<"["<<r.b<<"X"<<r.h<<"]"<<"("<<r.b*r.h<<")";
}

// IMPLEMENTARE UNA LISTA DINAMICA ORDINATA DI RETTANGOLI...

int main(){

    Rettangolo r1;
    Rettangolo r2(50,20);

    cout << r1 << endl;
    cout << r2 << endl;
    Rettangolo r3(20,50);
    Rettangolo r4(10,5);

    cout << r3 << endl;
    cout << r4 << endl;

    cout << (r1 == r2) << endl;
    cout << (r1 == r3) << endl;
    cout << (r1 == r4) << endl;
    cout << (r2 == r3) << endl;
    cout << (r2 == r4) << endl;

    return 0 ;
}
