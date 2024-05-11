#include <iostream>
using namespace std;

class Nodo{
	public:
		int valore;
		Nodo* succ;
};

class ListaSemplice{
	private:
		Nodo* testa;
		
	public:
		// costruttore
		ListaSemplice(){
			testa = NULL;
		}
		
		// distruttore
		~ListaSemplice();
		
		Nodo* getTesta(){
			return testa;
		}
		
		// inserimento in testa
		void inserisci(int val);
		// inserimento in posizione determinata
		void inserisci(Nodo* precedente, int val);
		// inserimento dopo un valore esistente
		void inserisciInCoda(int val);
		// metodo per la ricerca
		Nodo* ricerca(int val);
		// rimuove il primo elemento che contiene il valore
		void rimuovi(int val);
		
		// overloading per la stampa
		friend
		ostream& operator<<(ostream& out, const ListaSemplice& ls);
};

ListaSemplice::~ListaSemplice(){
	Nodo* iter = this->testa;
	while(iter!=NULL){
		Nodo* tmp = iter->succ;
		delete iter; // libero la locazione di memoria associata all'oggetto puntato da iter
		iter = tmp;
	}
}

ostream& operator<<(ostream& out, const ListaSemplice& ls){
	Nodo* iter = ls.testa;
	while(iter!=NULL){
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

void ListaSemplice::inserisci(Nodo* precedente, int val){
	Nodo* nuovo = new Nodo;
	nuovo->valore = val;
	nuovo->succ = precedente->succ;
	precedente->succ = nuovo;
}

void ListaSemplice::inserisciInCoda(int val){
	Nodo* nuovo = new Nodo;
	nuovo->valore = val;
	nuovo->succ = NULL;
	
	Nodo* iter = this->testa;
	if(iter==NULL)
		this->testa = nuovo;
	else{
		while(iter->succ!=NULL)
			iter = iter->succ;
		iter->succ = nuovo;
	}
	
}

Nodo* ListaSemplice::ricerca(int val){
	Nodo* p;
	for(p=this->testa; p!=NULL; p=p->succ)
		if(p->valore == val)
			return p;
	return NULL;
}

void ListaSemplice::rimuovi(int val){
	Nodo* prec;
	Nodo* curr;
	
	//Lista vuota
	if(this->testa==NULL)
		cout << "Lista vuota: impossibile rimuovere elementi" << endl;
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
		while((curr!=NULL) && (curr->valore!=val)){
			prec = prec->succ;
			curr = curr->succ;
		}
		if(curr!=NULL){
                prec->succ = curr->succ;
                delete curr;
        }
			
	}
}

int main(){
	ListaSemplice lista;
	
	cout << lista << endl;
	lista.inserisci(20);
	cout << lista << endl;
	lista.inserisci(10);
	Nodo* tmp = lista.getTesta();
	cout << lista << endl;
	lista.inserisci(5);
	cout << lista << endl;
	lista.inserisci(tmp, 18);
	cout << lista << endl;
	
	Nodo* p = lista.getTesta();
	while((p->valore!=10) && (p!=NULL))
		p = p->succ;
	
	int x;
	cout << "Inserisci un numero da inserire dopo il 10:\t";
	cin >> x;
	
	if(p!=NULL)
		lista.inserisci(p,x);
	cout << lista << endl;
	
	lista.inserisciInCoda(15);
	lista.inserisciInCoda(25);
	lista.inserisciInCoda(45);
	cout << lista << endl;
	
	cout << "Inserisci un numero da cercare nella lista:\t";
	cin >> x;
	Nodo* np;
	np = lista.ricerca(x);
	if(np)
		cout << "L'elemento e' presente nella lista" << endl;
	else
		cout << "Elemento non e' presente nella lista" << endl;

	cout << "Inserisci elemento da eliminare:\t";
	cin >> x;
	lista.rimuovi(x);
	cout << lista << endl;		
	
	return 0;
}
