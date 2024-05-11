/*
Esercizio 3: Algoritmo BFS usando matrici di adiacenza
*/
#include <iostream>
#include <math.h>

using namespace std;

// definisco delle costanti per i colori dei nodi
#define W 0
#define G 1
#define B 2
#define inf len+1    // definisco un valore infinito
                    // (nessun cammino minimo puo' essere piu lungo di len)


// mi serve una classe coda per mantenere i vertici grigi
class Coda {
private:
	int* VettoreCoda;
	int DimCoda;
	int testa;
	int fine;
	int num_elementi;
public:
	Coda(int DimCoda); //Costruttore della coda
	void Enqueue(int elemento); //Inserisce un elemento nella coda
	int Dequeue();  //Estrae un elemento dalla coda
	int Testa(); // Legge l'elemento in testa alla coda senza estrarlo
	int CodaVuota() {return (num_elementi==0);} // Verifica se la coda è vuota
	int CodaPiena() {return (num_elementi==DimCoda);} // Verifica se la coda è piena
};

Coda::Coda(int len) {
	DimCoda=len;
	VettoreCoda = new int[len];
	testa=0; fine=-1; num_elementi=0;
}

void Coda::Enqueue(int x)
{
	if (this->CodaPiena())
		cerr << "Coda piena! \n";
	else {
		fine=(fine + 1) % DimCoda;
		VettoreCoda[fine]=x;
		num_elementi++;
		}
}

int Coda::Testa()
{
	return testa;
}


int Coda::Dequeue()
{	int x;

	if (CodaVuota()) {
		cerr << "Coda Vuota!" << endl;
		return -1;  }
	else 	{
		x=VettoreCoda[testa];
		testa=(testa+1) % DimCoda;
		num_elementi--;
		return x;
		}
}

template <class H> class MGraph {
	private:
		int len, n, m;
		/* 	n numero di nodi effettivo,
			m numero di archi effettivo,
			len numero massimo di nodi
		*/
		int **M; //Matrice di adiacenza
		H **K;  // Matrice degli indici
		int *d, *p;
		// d -> distanze dalla sorgente durante la BFS
		// p -> array dei predecessori



		int findIndex(H x) {
		// Associa un indice al nodo (se esiste)
			for(int i=0; i<n; i++)
				if(*K[i] == x) return i;
			return -1;
		}

		void printPath(int x) {
			if(x==-1) return;
			if(p[x]==-1) cout << x;
			else {
				printPath(p[x]);
				cout << "->" << x;
			}
		}

	public:
		MGraph(int len) {
			this->len = len;
			n = m = 0;
			d = new int[len]; /* vettore delle distanze
								(dalla sorgente)
								*/
			p = new int[len]; // vettore dei precedenti

			M = new int*[len];
			for(int i=0; i<len; i++) {
				M[i] = new int[len];
				for(int j=0; j<len; j++)
					M[i][j] = 0;
			}
			K = new H*[len];
			for(int i=0; i<len; i++) K[i] = NULL;
		}

		MGraph<H>* addNode(H k) {
			if(n==len) return this;
			if(findIndex(k)>=0) return this;
			K[n] = new H(k);
			n++;
			return this;
		}

		MGraph<H>* addEdge(H x, H y) {
			int i = findIndex(x);
			int j = findIndex(y);
			if(i<0 || j<0) return this;
			if(!M[i][j]) {
				M[i][j] = 1;
				m++;
			}
			return this;
		}

		void print() {
			for(int i=0; i<n; i++) {
				cout << "(" << i << ", " << *K[i] << ")" << " : ";
				for(int j=0; j<n; j++) {
					if(M[i][j]) cout << *K[j] << " ";
				}
				cout << endl;
			}
		}

		void BFS(int s) {
		    bool debug = true; // se == true stampo lo stato dei nodi (i loro colori)
			int c[len]; // lista dei colori
			Coda *Q = new Coda(len);
			//iniz.
			for(int i=0; i<n; i++) {
				c[i] = W;
				p[i] = -1;
				d[i] = inf;
			}
			Q->Enqueue(s);
			c[s] = G;
			d[s] = 0;
			while(!Q->CodaVuota()) {

                // posso stampare qui lo stato dei colori (utile per comprensione/debug)
                if(debug){
                    stampaColoriNodi(c);
                    cout << endl;
                }
				int x = Q->Dequeue();
				// visito la lista di adj del nodo x
				for(int i=0; i<n; i++) {
					if(M[x][i]==1) {
						if(c[i]==W) {
							c[i] = G;
							Q->Enqueue(i);
							p[i] = x;
							d[i] = d[x]+1;
						}
					}
				}
				c[x] = B;
				if(debug) cout << "ho completato la visita di " << *K[x] << endl;
			}
			// stampo le distanze
			cout << "Distanze dalla sorgente:" << endl;
			for(int i=0; i<n; i++) {
				cout << "[" << *K[i] << "]->";
				if(d[i]==inf) cout << "inf." << endl;
				else cout << d[i] << endl;
			}
			cout << endl;
		}

		void BFS(H x) {
			int s = findIndex(x);
			if(s>=0) BFS(s);
		}

		// se il parametro 'sologrigi' e' true, stampa solo quelli grigi
        void stampaColoriNodi(int* colors, bool sologrigi=false){
            for(int i=0; i<n; i++) {
				if(sologrigi&& colors[i]!=G) continue;

                cout << " " << *K[i];
                switch(colors[i]){
                    case W: cout << "(w)";break;
                    case G: cout << "(g)";break;
                    case B: cout << "(b)";break;
                }

            }
        }
};

int main() {


	MGraph<char> *Gr = new MGraph<char>(9);
	Gr->addNode('A')->addNode('B')->addNode('C')->addNode('D');
	Gr->addNode('E')->addNode('F')->addNode('G')->addNode('H');
	Gr->addNode('I');

	Gr->addEdge('A','I')->addEdge('A','B');
	Gr->addEdge('B','I');
	Gr->addEdge('C','E');
	//Gr->addEdge('D','F')->addEdge('D','G')->addEdge('D','H');
	Gr->addEdge('E','D')->addEdge('E','A');
	Gr->addEdge('F','G')->addEdge('F','D');
	Gr->addEdge('G','F');
	Gr->addEdge('I','C');
	Gr->print();
	Gr->BFS(0);
	return 0;
}
