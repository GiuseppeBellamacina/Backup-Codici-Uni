
#include <iostream>
using namespace std;

struct Nodo{
    int valore;
    Nodo* succ;
    Nodo* prec;
};

class ListaDoppiaCircolare{
    Nodo* testa;

public:
    ListaDoppiaCircolare() {testa = nullptr;}
    ~ListaDoppiaCircolare();
    void inserisci(int);
    Nodo* getTesta() {return testa;}

    friend
    ostream& operator<<(ostream& out, const ListaDoppiaCircolare& ls);
};

ListaDoppiaCircolare::~ListaDoppiaCircolare(){
    Nodo* iter;
    if(testa!=nullptr)
        iter=testa->succ;
    else return;

    while(iter!=testa){
        Nodo* tmp = iter->succ;
        delete iter;
        iter = tmp;
    }
    delete testa;
}


ostream& operator<<(ostream& out, const ListaDoppiaCircolare& ls){

    if(ls.testa==nullptr){
        out << "Lista vuota." << endl;
        return out;
    }

    Nodo* iter = ls.testa; //***

    do{
        out << "Valore\t" << iter->valore << endl;
        out << "\t -->";
        // stampo il successivo
        if(iter->succ != nullptr)
            out << iter->succ->valore;
        else
            out << "NULL";
        out << endl;
        // stampo il precedente
        out << "\t <--";
        if(iter->prec != nullptr)
            out << iter->prec->valore;
        else
            out << "NULL";
        out << endl << endl;
        iter = iter->succ;

    }while(iter!=ls.testa);

    return out;
}


void ListaDoppiaCircolare::inserisci(int val){

    Nodo* nuovo = new Nodo;
    nuovo->valore = val;
    if(testa!=nullptr){
        nuovo->succ = testa->succ;
        testa->succ = nuovo;
        nuovo->prec = testa;
        nuovo->succ->prec = nuovo;
    }
    else{
        nuovo->succ = nuovo;
        nuovo->prec = nuovo;
        testa = nuovo;
    }

}


int main(){

    ListaDoppiaCircolare lista;

    cout << lista;

    cout << "Inserisco un elemento..." << endl;
   // lista.inserisci(101);
    //cout << lista;

    for(int i=0;i<10;i++)
        lista.inserisci(i);

    cout << lista;

    return 0;
}

