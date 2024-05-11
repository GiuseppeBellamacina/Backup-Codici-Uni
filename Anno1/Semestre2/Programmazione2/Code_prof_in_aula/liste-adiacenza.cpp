/*
Esercizio 1: Rappresentazione di Grafi usando liste di adiacenza
*/

#include <iostream>
using namespace std;


template <class T> struct Nodo {
	T valore;
	Nodo<T>* succ;
};

template <class T> class Lista{
public:
	Lista() {testa=NULL;}
	~Lista();
	void print(); // in alternativa ad operator<<
	void insert(T val);
	Nodo<T>* getTesta() {return testa;}
	Nodo<T>* search(T val);
private:
	Nodo<T>* testa;

friend
ostream& operator<<(ostream& out, const Lista& ls){
    Nodo<T>* iter=ls.testa;

	while (iter!=NULL) {
		out << " " << iter->valore << "\t";
		iter=iter->succ;
		}
		return out;
}

};

template <class T> Lista <T> ::~Lista()	{
	Nodo<T>* iter=this->testa;

	while(iter!=NULL)	{
		Nodo<T>* temp= iter->succ;
		delete iter;
		iter=temp;
	}
}


template <class T> void Lista <T> ::print()
{
	Nodo<T>* iter=this->testa;

	while (iter!=NULL) {
		cout << " " << iter->valore << "\t";
		iter=iter->succ;
		}
}

template <class T> void Lista <T>::insert(T val)
{
	Nodo<T>* nuovo= new Nodo<T>;

	nuovo->valore=val;
	nuovo->succ=this->testa;
	this->testa=nuovo;
}

template <class T> Nodo<T>* Lista <T> ::search(T indice)
{
	Nodo<T>* p;

	for (p=this->testa; p!=NULL; p=p->succ)
		if (p->valore==indice)
			return p;
	return NULL;
}



template <class H> class LGraph {
	private:
		int len, n, m;
		/*	len numero massimo di nodi
            n numero di nodi effettivo,
			m numero di archi effettivo,
		*/
		//int t;
		H **K;// lista di puntatori ad elementi di tipo H
		Lista<int> **Adj; // lista di puntatori ad elementi di tipo Lista<int>

		int findIndex(H x) {
		// Trova l'indice associato al nodo
			for(int i=0; i<n; i++)
				if(*K[i] == x) return i;
			return -1;
		}

	public:
		LGraph(int len) {
			this->len = len;
			n = m = 0;
			K = new H*[len];
			for(int i=0; i<len; i++)
                K[i] = NULL;
			Adj = new Lista<int>*[len];
			for(int i=0; i<len; i++)
                // inizializzo ogni lista di adiacenza coma un Lista<int>
				Adj[i] = new Lista<int>();
		}

		LGraph<H>* addNode(H k) {
		// Aggiunge un nodo al grafo (se non già presente)
			if(n==len) return this;
			if(findIndex(k)>=0) return this;
			K[n] = new H(k);
			n++;
			return this;
		}

		LGraph<H>* addEdge(H x, H y) {
		// Aggiunge un arco al grafo (se non già presente)
			int i = findIndex(x);
			int j = findIndex(y);
			if(i<0 || j<0) return this;
			if(!Adj[i]->search(j)) {
				Adj[i]->insert(j);
				m++;
			}
			return this;
		}

		void print() {
		    bool semplice = false; // seleziona la modalita' di stampa (vedi dopo)
			for(int i=0; i<n; i++) {
				cout << "(" << i << ", " << *K[i] << ")" << " : ";
				// VERSIONE 1 (semplice)
				 // stampo la lista degli indici (int) nella lista di adiacenza dell'elemento K[i]
				if(semplice)
                    cout << *Adj[i];
                else{
				// VERSIONE 2 (meno semplice)..
				// stampo lista di indici e valori dei nodi nella
				 // lista di adiacenza
				//      &(...) --> 'puntatore di (...)  '
				//      *(...) --> 'valore puntato da (...) '
                  //  Nodo<int>* iter =&(*Adj[i]->getTesta());
                    Nodo<int>* iter =Adj[i]->getTesta();
                    //for(int c=0; iter!=NULL; iter=iter->succ, c++){
                    for(; iter!=NULL; iter=iter->succ){
                        cout << "\t(" << iter->valore << ", " << *K[iter->valore] << ")";
                    }

                }
				cout << endl;


			}
		}
};



int main() {
	LGraph<char> *Gr = new LGraph<char>(9);

	Gr->addNode('A')->addNode('B')->addNode('C')->addNode('D');
	Gr->addNode('E')->addNode('F')->addNode('G')->addNode('H');
	Gr->addNode('I');

	Gr->addEdge('A','I')->addEdge('A','B');
	Gr->addEdge('B','I');
	Gr->addEdge('C','E');
	Gr->addEdge('D','F')->addEdge('D','G')->addEdge('D','H');
	Gr->addEdge('E','D')->addEdge('E','A');
	Gr->addEdge('F','G')->addEdge('F','D');
	Gr->addEdge('G','F');
	Gr->addEdge('I','C');

	Gr->print();


}
