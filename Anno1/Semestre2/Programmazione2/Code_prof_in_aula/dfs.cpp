/*
Esercizio 4: Algoritmo DFS usando matrici di adiacenza
*/
#include <iostream>
using namespace std;

#define W 0
#define G 1
#define B 2
#define inf len+1


template <class H> class MGraph {
	private:
		int len, n, m;
		/* 	n numero di nodi effettivo,
			m numero di archi effettivo,
			len numero massimo di nodi
		*/
		int **M; //Matrice di adiacenza
		int t;   //serve per tener conto dei tempi di visita dei nodi nella DFS

		H **K;  // Matrice degli indici
		/*  d: distanze da sorgente
            p: predecessori,
            f: tempi di fine,
            c: colori nodi,
            r: array radici */
		int *d, *p, *f, *c, *r;
		int current_root;
		//int lastBFSSource;


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
			f = new int[len]; // tempi di completamento
			c = new int[len]; // colori dei nodi
			r = new int[len]; // vettore delle radici

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


		void DFSVisit(int v) {
			c[v] = G;
			d[v] = t++;
			r[v] = current_root;
			for(int u=0; u<n; u++) {
				if(M[v][u]==1) {
					if(c[u]==W) {
        // i tempi di scoperta/completamento hanno una struttura a parentesi
        //stampando "(" quando un nodo viene scoperto e ")" quando viene completato
        // la storia delle scoperte e completamenti produce un'espress. ben formata
                        cout << "( " << *K[u] << " ";
						p[u]=v;
						DFSVisit(u);
					}
				}
			}
			c[v] = B;
			cout << " ) ";
			f[v] = t++;
		}

		void DFS() {

		    cout << endl << "DFS visit: ";
			t = 0;
			for(int i=0; i<n; i++) {
				c[i] = W;
				p[i] = -1;
			}
			for(int i=0; i<n; i++)
				if(c[i]==W) {
					current_root = i;
					//vado a capo per capire quante volte cicla (se connesso solo 1 volta)
                    cout <<endl<< "( " << *K[i] << " ";
					DFSVisit(i);
				}
		}
};

int main() {
	MGraph<char> *Gr = new MGraph<char>(9);

/*
In questi esempi di codice:

Gr e' un grafo connesso
Gr_2 e' un grafo non connesso con 2 componenti
nel secondo caso la DFS produce due alberi
 */
 	cout << endl << "****** GRAFO GR *********" << endl;

	Gr->addNode('a')->addNode('b')->addNode('c')->addNode('d');
	Gr->addNode('e')->addNode('f')->addNode('g')->addNode('h');
	Gr->addNode('i');

	Gr->addEdge('a','i')->addEdge('a','b');
	Gr->addEdge('b','i');
	Gr->addEdge('c','e');
	Gr->addEdge('d','f')->addEdge('d','g')->addEdge('d','h');
	Gr->addEdge('e','d')->addEdge('e','a');
	Gr->addEdge('f','g')->addEdge('f','d');
	Gr->addEdge('g','f');
	Gr->addEdge('i','c');


	Gr->print();
	//Gr->SCC();
	Gr->DFS();


	cout << endl << "****** GRAFO GR_2 *********" << endl;

    MGraph<char> *Gr_2 = new MGraph<char>(9);
	Gr_2->addNode('a')->addNode('b')->addNode('c')->addNode('d');
	Gr_2->addNode('e')->addNode('f')->addNode('g')->addNode('h');
	Gr_2->addNode('i');



	Gr_2->addEdge('a','i')->addEdge('a','b');
	Gr_2->addEdge('b','i');
	Gr_2->addEdge('c','e');
	Gr_2->addEdge('d','f')->addEdge('d','g')->addEdge('d','h');
	// rispetto a prima escludo l'arco e->d avro' un grafo non connesso
	//Gr_2->addEdge('e','d')->addEdge('e','a');
	Gr_2->addEdge('e','a');
	Gr_2->addEdge('f','g')->addEdge('f','d');
	Gr_2->addEdge('g','f');
	Gr_2->addEdge('i','c');

    Gr_2->print();
	Gr_2->DFS();


}
