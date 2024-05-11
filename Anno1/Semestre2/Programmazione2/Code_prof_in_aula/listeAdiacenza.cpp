
#include <iostream>
using namespace std;

template <class T> struct Nodo{
    T valore; Nodo<T>* succ;
}
template <class T> class Lista{
public:
    Lista() {testa = NULL;}
  //  void print();
    void insert(T val);
    Nodo<T>* getTesta() {return testa;}
    Nodo<T>*  search(T val);

private:
    Nodo<T>* testa;

friend ostream& operator<<(ostream& out, const Lista& ls){
    Nodo<T>* iter = ls.testa;
    while(iter!=NULL){
        out << " " << iter->valore << "\t";
        iter = iter->succ;
    }
    return out;
}
};



template <class T> void Lista<T>::insert(T val){
    Nodo<T>* nuovo = new Nodo<T>;
    nuovo->valore = val,
    nuovo->succ = this->testa;
    this->testa = nuovo;
}

template <class T> Nodo<T>* Lista<T>::search(T val){
    Nodo<T>* p;
    for(p=this->testa;p!=NULL;p=p->succ)
        if(p->valore == val) return p;
    return NULL;
}


template <class H> class LGraph{
private:
    int len, n, m;

    H **K; // lista di puntatori ad elementi di tipo H
    Lista<H> **Adj;

    int findIndex(H x){
        for(int i=0;i<n;i++)
            if(*K[i]==x) return i;
        return -1;
    }

public:

}



