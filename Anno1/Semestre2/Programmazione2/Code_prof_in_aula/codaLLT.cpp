
#include <iostream>
using namespace std;

template <typename T>
class Nodo{
public:
    T valore;
    Nodo<T>* succ;
    Nodo(T d): valore(d), succ(nullptr){}
};


template <typename T>
class Coda{
    Nodo<T> *fronte, *fine;
public:
    Coda(){fronte = fine = nullptr;}
    ~Coda(){
    	Nodo<T>* temp;
    	while(fronte != NULL){
        	temp = fronte;
        	fronte = fronte->succ;
        	delete temp;
    	}
    	fine = NULL;
	}
    bool isEmpty()const { return fronte ==nullptr;}
    void enqueue(T x);
    T dequeue();

    template <typename U>
    friend
    ostream& operator<<(ostream& out, const Coda<U>);
};

template <typename T>
void Coda<T>::enqueue(T x){
    Nodo<T> *tmp = new Nodo<T>(x);
    if(fine == nullptr){
        fronte = fine = tmp;
        return;
    }

    fine->succ = tmp;
    fine = tmp;
}

template <typename T>
T Coda<T>::dequeue(){
    if(fronte == nullptr){
        cout << "Coda vuota!" << endl;
        exit(-1);
    }

    Nodo<T> * tmp = fronte;
    T retVal = tmp->valore;
    fronte = fronte->succ;

    if(fronte==nullptr)
        fine = nullptr;
    delete tmp;
    return retVal;
}


template <typename U>
ostream& operator<<(ostream& out, const Coda<U> q){
    Nodo<U> *iter;
    out << endl << "Visualizzazione coda:" << endl;
    if(q.isEmpty())
        out << "Coda vuota"<< endl;
    else{
        out << "<--";
        for(iter=q.fronte; iter!=nullptr; iter=iter->succ)
            out << "|" << iter->valore;
        out << "|<--" << endl;
    }

    out << endl;
    return out;
}


int main(){

    Coda<char> cq;
    cq.enqueue('A');
    cq.enqueue('B');
    cq.enqueue('C');
    cq.enqueue('D');
    cq.enqueue('E');
    cq.enqueue('F');

    cout << cq;


    cq.dequeue();
    cq.dequeue();
    cq.dequeue();

    cout << cq;
    cq.~Coda();
    cout << cq;
    return 0;
}
