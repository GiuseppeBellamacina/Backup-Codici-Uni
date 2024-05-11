#include <iostream>
using namespace std;

class Nodo{
public:
    int valore;
    Nodo* succ;
};


class ListaSemplice{
public:
    ListaSemplice(){testa=nullptr;}
    ~ListaSemplice();
    Nodo* getTesta(){return testa;}
    // inserimento in testa
    void inserisci(int val);
    // inserimento dopo un nodo esistente
    void inserisci(Nodo* precedente, int val);
    void inserisciInCoda(int val);
    Nodo* ricerca(int val);
    void rimuovi(int val);
    void inverti();

    friend
    ostream& operator<<(ostream& out, const ListaSemplice& ls);
private:
    Nodo* testa;

};

//  testa -> | 5 | -> | 6 | -> nullptr
//                      ^
//                     iter
ListaSemplice::~ListaSemplice(){
    Nodo* iter = this->testa;
    while(iter!=nullptr){
        Nodo* tmp = iter->succ;
        delete iter;
        iter = tmp;
    }
}

ostream& operator<<(ostream& out, const ListaSemplice& ls){
    Nodo* iter = ls.testa;
// for(Nodo* iter=ls.testa;iter!=nullptr;iter=iter->succ)
    while(iter!=nullptr){
        out << iter->valore << " --> ";
        iter = iter->succ;
    }
    cout << "NULL" << endl;
    return out;
}


void ListaSemplice::inserisci(int val){
    Nodo* nuovo = new Nodo;
    nuovo->valore = val;
    nuovo->succ = this->testa;
    this->testa = nuovo;
}

// inserimento dopo un nodo esistente
void ListaSemplice::inserisci(Nodo* precedente, int val){
    Nodo* nuovo = new Nodo;
    nuovo->valore = val;
    nuovo->succ = precedente->succ;
    precedente->succ = nuovo;
}

void ListaSemplice::inserisciInCoda(int val){
    Nodo* nuovo = new Nodo;
    nuovo->valore = val;
    nuovo->succ = nullptr;

    Nodo* iter = this->testa;
    if(iter == nullptr)
        this->testa = nuovo;
    else{
        while(iter->succ!=nullptr)
            iter = iter->succ;
        iter->succ = nuovo;
    }
}

Nodo* ListaSemplice::ricerca(int val){
    Nodo* p;
    for(p=this->testa;p!=nullptr;p=p->succ)
        if(p->valore == val)
            return p;
    return nullptr;
}


void ListaSemplice::rimuovi(int val){
    Nodo* prec;
    Nodo* curr;

    //Lista vuota
    if(this->testa == nullptr)
        cout << "Lista vuota: impossibile rimuovere elementi"<<endl;
    // se l'elemento si trova nella testa...
    else if(this->testa->valore == val){
        prec = this->testa;
        this->testa = prec->succ;
        delete prec;
    }
    // caso generico
    else{
            prec = this->testa;
            curr = this->testa->succ;
//          la versione commentata darebbe errore nel caso in cui
//          l'elemento da eliminare non fosse nella lista
//            while(  (curr->valore!=val) && (curr!=nullptr)  )
            while(  (curr!=nullptr)  && (curr->valore!=val)   ){
                prec = prec->succ;
                curr = curr->succ;
            }

            if(curr!=nullptr){
                prec->succ = curr->succ;
                delete curr;
            }

    }

}

void ListaSemplice::inverti()
{
    Nodo* prev = nullptr;
    Nodo* current = testa;
    Nodo* next = nullptr;
    while(current!=nullptr){
        next = current->succ;
        current->succ=prev;
        prev=current;
        current=next;
    }
    testa = prev;
}

void boo(Nodo* testa){
    if(testa==nullptr) return;
    boo(testa->succ);
    cout<<testa->valore<<endl;
}



int main(){
    ListaSemplice lista;

    lista.inserisci(20);
    lista.inserisci(10);
    lista.inserisci(5);
    cout << lista;
    lista.inverti();
    cout << lista;

    Nodo* p = lista.getTesta();
    // cerco il nodo &p che contiene il valore 10
    while((p->valore!=10) && (p!=nullptr))
        p = p->succ;

    int x;
    cout << "Inserisci un numero da inserire dopo il 10:\t";
    cin >> x;

    if(p!=nullptr)
        lista.inserisci(p,x);

    cout << lista;

    lista.inserisciInCoda(15);
    lista.inserisciInCoda(25);
    lista.inserisciInCoda(45);

    cout << lista;

    cout << "Inserisci un intero da cercare nella lista:\t";
    cin >> x;
    Nodo* np;
    np = lista.ricerca(x);
    if(np!=nullptr)
        cout << "L'elemento e' presente nella lista" << endl;
    else
        cout << "Elemento non trovato!!!" << endl;

    cout << "Inserisci un elemento da eliminare\t";
    cin >> x;
    lista.rimuovi(x);
    cout << lista;

    return 0;
}
