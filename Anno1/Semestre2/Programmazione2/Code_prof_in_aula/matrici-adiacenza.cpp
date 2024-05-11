/*

Esercizio 2: Rappresentazione di Grafi usando matrici di adiacenza
*/
#include <iostream>
using namespace std;

template <class H> class MGraph {
	private:
		int len, n, m;
		/* 	n numero di nodi effettivo,
			m numero di archi effettivo,
			len numero massimo di nodi
		*/
		int **M; //Contiene gli indici corrispondenti ai vari nodi
		H **K; // Contiene i valori di tipo H dei nodi

		int findIndex(H x) {
			for(int i=0; i<n; i++)
				if(*K[i] == x) return i;
			return -1;
		}

	public:
		MGraph(int len) {
			this->len = len;
			n = m = 0;
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
};


int main() {
	MGraph<char> *Gr = new MGraph<char>(9);

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
