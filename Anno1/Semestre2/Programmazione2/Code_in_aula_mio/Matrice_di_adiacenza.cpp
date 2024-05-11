#include <iostream>
using namespace std;

// matrice di adiacenza
template <class H> class MGraph{
	private:
		int len, n, m;
		/* len: # max di nodi
		   n: # effettivo di nodi
		   m: effettivo di archi */
		int** M; // matrice degli indici
		H** K; // matrice di elementi di tipo H
		
		// dato un valore di tipo H, restituisce l'indice
		int findIndex(H x){
			for(int i=0; i<len; i++)
				if(*K[i] == x) return i;
			return -1;
		}
	public:
		MGraph(int l): len(l){
			n = m = 0;
			// inizializzo la matrice M a 0
			M = new int*[len];
			for(int i=0; i<len; i++){
				M[i] = new int[len];
				for(int j=0; j<len; j++)
					M[i][j] = 0;
			}
			K = new H*[len];
			for(int i=0; i<len; i++) K[i] = NULL;
		}
		
		MGraph<H>* addNode(H k){ // si può fare void, ma vediamo perchè va fatta così
			if(n==len) return this;
			if(findIndex(k) >= 0) return this;
			K[n] = new H(k);
			n++;
			return this;
		}
		
		MGraph<H>* addEdge(H x, H y){
			int i = findIndex(x);
			int j = findIndex(y);
			if(i<0 || j<0) return this;
			if(!M[i][j]){
				M[i][j] = 1;
				m++;
			}
			return this;
		}
		
		void print(){
			for(int i=0; i<n; i++){
				cout << "(" << i << "," << *K[i] << ")" << " : ";
				for(int j=0; j<n; j++){
					if(M[i][j])
						cout << *K[j] <<" ";
				}
				cout << endl;
			}
		}
};

int main(){
	MGraph<char> *Gr = new MGraph<char>(9);
	// con quella cosa dell'addNode col puntatore si può scrivere così
	Gr->addNode('A')->addNode('B')->addNode('C')->addNode('D');
	Gr->addNode('E')->addNode('F')->addNode('G')->addNode('H');
	Gr->addNode('I');
	
	Gr->addEdge('A','I')->addEdge('A','B')->addEdge('B','I');
	
	Gr->print();
	
	return 0;
}
