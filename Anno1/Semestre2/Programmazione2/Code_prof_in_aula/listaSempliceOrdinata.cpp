#include <iostream>
using namespace std;

class Nodo{
public:
    Nodo(int x):valore(x){}
    int valore;
    Nodo* succ;
};

class ListaSempliceOrdinata{
Nodo* testa;
public:
    ListaSempliceOrdinata(){testa = nullptr;}
    ~ListaSempliceOrdinata();
    Nodo* getTesta(){return testa;}

    void inserisci(int val);
    Nodo* ricerca(int val);
    void rimuovi(int val);

    friend
    ostream& operator<<(ostream& out, const ListaSempliceOrdinata& ls);
};


ListaSempliceOrdinata::~ListaSempliceOrdinata(){
    Nodo* iter = this->testa;
    while(iter!=nullptr){
        Nodo* tmp = iter->succ;
        delete iter;
        iter = tmp;
    }
}

ostream& operator<<(ostream& out, const ListaSempliceOrdinata& ls){
    Nodo* iter = ls.testa;
// for(Nodo* iter=ls.testa;iter!=nullptr;iter=iter->succ)
    while(iter!=nullptr){
        out << iter->valore << " --> ";
        iter = iter->succ;
    }
    cout << "NULL" << endl;
    return out;
}



void ListaSempliceOrdinata::inserisci(int val){
    Nodo* nuovo = new Nodo(val);
    Nodo* iter = this->testa;

    // caso 1: lista vuota
    if(this->testa == nullptr){
        nuovo->succ = nullptr;
        this->testa = nuovo;
    }
    // caso 2: se val<testa faccio un inserimento in testa
    else if(this->testa->valore >= val){
        nuovo->succ = this->testa;
        this->testa = nuovo;
    }
    // caso generico
    else{
        while(  (iter->succ!=nullptr)  && (val > iter->succ->valore)  )
            iter = iter->succ;
        nuovo->succ = iter->succ;
        iter->succ = nuovo;
    }

}

int main(){
    ListaSempliceOrdinata lista;
    lista.inserisci(10);
    lista.inserisci(5);
    lista.inserisci(20);

    cout << lista;

    int x;
    cout << "inserisci 10 elementi... " << endl;

    for(int i=0;i<10;i++){
        cout << "elemento:\t";
        cin >> x;
        lista.inserisci(x);
        cout << lista;
    }

    return 0;
}
