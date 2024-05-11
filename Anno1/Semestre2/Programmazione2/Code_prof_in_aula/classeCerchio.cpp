
#include <iostream>
using namespace std;

enum Colore {ROSSO, GIALLO, VERDE, BLU};
class Cerchio {
    double raggio;
    Colore col;

public:
    Cerchio() { raggio = 1; col = ROSSO; cout << "costr default" << endl;}
    Cerchio(double r, Colore c): raggio(r), col(c)
    { cout << "costr 2" << endl;}

    // Costruttore con delega
    Cerchio(double r): Cerchio(r,ROSSO)
    { cout << "costr 3" << endl;}

    double circonferenza() const { return 2*raggio*3.14;}
    double getRaggio() const { return raggio;}
};
/* se circonferenza non e' dichiarata 'const', possono succedere cose strane...
class SubCerchio : public Cerchio{
public:
    double circonferenza(){ this.raggio = 0; return 100;};
};  */

// top-level function per l'area
double areaCerchio(Cerchio c){
    return c.getRaggio()*c.getRaggio()*3.14;
}

double area(Cerchio& c){
    cout << "area() senza const." << endl;
    return c.getRaggio()*c.getRaggio()*3.14;
}

double area(const Cerchio& c){
    cout << "area() con const." << endl;
    return c.getRaggio()*c.getRaggio()*3.14;
}


int main(){

    Cerchio c1 (10.0); // functional form (pericolosa...)
    Cerchio c2 = 20.0; // assignment initialization
    Cerchio c3{30.0};   // uniform initialization
    Cerchio c4 = {40.0};
    // finora viene chiamato solo il secondo costruttore

    Cerchio cc1;
    Cerchio cc2(); // <<-- tipico errore con func. iniz. (interpretato come func. declaration)
    Cerchio cc3{};

    cout << "Circonferenza cc1:" << cc1.circonferenza() << endl;
//    cout << "Circonferenza cc2:" << cc2.circonferenza() << endl;
    cout << "Circonferenza cc3:" << cc3.circonferenza() << endl;


    cout << endl << "Calcolo di aree:" << endl;

    Cerchio c_d(2.3); cout << endl;
    Cerchio c_f(3.1f); cout << endl;
    Cerchio c_i(10); cout << endl;

    cout << "Utilizzo del metodo areaCerchio()" << endl;

    cout << "Area di c_d: " << areaCerchio(c_d) << endl;
    cout << "Area:\t" << areaCerchio(2.3) << endl;

    cout << endl << "Utilizzo del metodo area()" << endl;
    cout << "Area:\t" << area(2.3) << endl;
    cout << "Area:\t" << area(c_d) << endl;



    return 0;
}


