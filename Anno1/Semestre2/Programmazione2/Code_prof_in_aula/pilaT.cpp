
#include <iostream>
using namespace std;

enum StatoPila {OK, PIENA, VUOTA};

template <typename T>
class Pila{
private:
    int lunghezza;
    T* contenuto;
    int cima;
    StatoPila stato;
public:
    Pila(int l=10);
    ~Pila(){delete [] contenuto;}
    void push(T);
    T pop();
    int numElementi(){return cima+1;};
    int getLunghezza() {return lunghezza;}


    template<typename U>
    friend
    ostream& operator<<(ostream& out, const Pila<U>&p);
};

template <typename U>
ostream& operator<<(ostream& out, const Pila<U>&p){
    for(int i=p.cima;i>=0;i--)
        out << "["<< p.contenuto[i] << "]" << endl;
    return out;
}



template<typename T>
Pila<T>::Pila(int l){
    lunghezza = l;
    contenuto = new T[lunghezza];
    cima = -1;
    stato = VUOTA;
}
template<typename T>
void Pila<T>::push(T elem){
    if(stato!=PIENA)
        contenuto[++cima] = elem;
    else
        cout << "Pila piena!" << endl;
    if(cima == lunghezza-1)
        stato = PIENA;
    else
        stato = OK;
}


template <typename T>
T Pila<T>::pop(){
    int elem = 0;
    if(stato != VUOTA)
        elem = contenuto[cima--];
    else
        cout << "Pila vuota!" << endl;
    if(cima==-1)
        stato = VUOTA;
    else
        stato = OK;
    return elem;
}


int main(){
    Pila<int> iStack(6);
    iStack.push(1);
    iStack.push(2);
    iStack.push(3);
    cout << iStack;

    cout << "primo:\t\t" << iStack.pop() << endl;
    cout << "secondo:\t" << iStack.pop() << endl;
    cout << iStack;

    cout << endl;

    Pila <char> cStack;
    cStack.push('A');
    cStack.push('B');
    cStack.push('C');
    cStack.push('D');

    cout << cStack;
    return 0;


}

