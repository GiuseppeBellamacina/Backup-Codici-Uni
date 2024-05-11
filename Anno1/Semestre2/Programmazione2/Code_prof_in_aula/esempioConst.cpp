
#include <iostream>
using namespace std;

class ContoCorrente{
private:
    int saldo = 100000;

public:
    int& getSaldo(){ return saldo;}
    int const & getSaldoBuona() const { return saldo;}

    void printSaldo() const {
        cout << "Il tuo saldo e':\t" << saldo << endl;
        if(saldo<0)
            cout << "Attenzione!! il conto e' in passivo!!!" << endl;
    }
};


int main(){

    ContoCorrente A,B;
    A.printSaldo();

    int s = A.getSaldo();
    cout << "saldo: " << s << endl;

    A.getSaldo() = -5000;
    A.printSaldo();
    cout << endl;
   // B.getSaldoBuona() = -50000;
    B.printSaldo();

    return 0;
}
