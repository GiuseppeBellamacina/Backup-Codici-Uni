#include <iostream>
#include <ctime>
#include <math.h>
#include "List.cpp"
using namespace std;

#define W 0
#define G 1
#define B 2
#define inf len+1

class Queue {
	private:
		int len, n, head, tail;
		int *q;
		
	public:
		Queue(int len) {
			this->len = len;
			q = new int[len];
			n = 0;
			head = tail = 0;
		}
		int isEmpty() { return n==0; }
		void push(int x) {
			q[tail] = x;
			tail = (tail+1)%len;
			n++;
		}
		
		int pop() {
			if(n>0) {
				int t = q[head];
				head = (head+1) % len;
				n--;
				return t;
			}
			return -1;
		}
	
};

template <class H> class MGraph {
	private:
		int len, n, m;
		int **M;
		int t;
		H **K;
		int *d, *p, *f, *c, *r;
		int current_root;
		int lastBFSSource;
		
		
		int findIndex(H x) {
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
		
		void sort(int *a, int n, int *k) {
			for(int i=1; i<n; i++) {
				int j = i-1;
				while(j>=0 && k[a[j+1]]>k[a[j]]) {
					int t = a[j+1];
					a[j+1] = a[j];
					a[j] = t;
					j--;
				}
			}
		}
		
	public:
		MGraph(int len) {
			this->len = len;
			n = m = 0;
			d = new int[len];
			p = new int[len];
			f = new int[len];
			c = new int[len];
			r = new int[len];
			M = new int*[len];
			for(int i=0; i<len; i++) {
				M[i] = new int[len];
				for(int j=0; j<len; j++)
					M[i][j] = 0;
			}
			K = new H*[len];
			for(int i=0; i<len; i++) K[i] = NULL;
			lastBFSSource = -1;
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
			int c[len];
			Queue *Q = new Queue(len);
			//iniz.
			for(int i=0; i<n; i++) {
				c[i] = W;
				p[i] = -1;
				d[i] = inf;
			}
			Q->push(s);
			c[s] = G;
			d[s] = 0;	
			while(!Q->isEmpty()) {
				int x = Q->pop();
				for(int i=0; i<n; i++) {
					if(M[x][i]==1) {
						if(c[i]==W) {
							c[i] = G;
							Q->push(i);
							p[i] = x;
							d[i] = d[x]+1;
						}
					} 
				}
				c[x] = B;
			}
			lastBFSSource = s;
			for(int i=0; i<n; i++) {
				cout << "[" << i << "]->";
				if(d[i]==inf) cout << "inf." << endl;
				else cout << d[i] << endl;
			}
			cout << endl;
		}
		
		void BFS(H x) {
			int s = findIndex(x);
			if(s>=0) BFS(s);
		}
		
		int minDist(H x, H y) {
			int s = findIndex(x);
			if(s==-1) return inf;
			if(lastBFSSource!=s) BFS(s);
			int t = findIndex(y);
			if(t==-1) return inf;
			return d[t];
		}

		void minPath(H x, H y) {
			int s = findIndex(x);
			int t = findIndex(y);
			if(t==-1 || s==-1) {
				cout << "Non esiste alcun cammino" << endl;
				return;
			}
			if(lastBFSSource!=s) BFS(s);
			printPath(t);
			cout << endl;
		}
		
		int DFSVisit(int v) {
			//cout << "(" << v << ") " << endl;
			int cycle = 0;
			c[v] = G;
			d[v] = t++;
			r[v] = current_root;
			for(int u=0; u<n; u++) {
				if(M[v][u]==1) {
					if(c[u]==W) {
						p[u]=v;
						cycle |= DFSVisit(u);
					}
					if(c[u]==G) cycle = 1;
				}
			}
			c[v] = B;
			f[v] = t++;
			return cycle;		
		}
		
		int DFS() {
			int cycle = 0;
			t = 0;
			for(int i=0; i<n; i++) {
				c[i] = W;
				p[i] = -1;
			}
			for(int i=0; i<n; i++)
				if(c[i]==W) {
					current_root = i;
					cycle |= DFSVisit(i);
				}
			//for(int i=0; i<n; i++)
			//	cout << "[" << i << "] : " << r[i] << endl;
			return cycle;
		}
		
		void topSort() {
			int cycle = DFS();
			if(cycle) {
				cout << "Il grafo contiene un ciclo";
				return;
			}
			int *s = new int[n];
			for(int i=0; i<n; i++) s[i] = i;
			sort(s,n,f);
			for(int i=0; i<n; i++) {
				cout << "(" << s[i] << ", " << f[s[i]] << ") ";
			}
			cout << endl;
		}
		
		void getCC(int v) {
			int **T;
			T = new int*[n];
			for(int i=0; i<n; i++) {
				T[i] = new int[n];
				for(int j=0; j<n; j++)
					T[i][j] = M[j][i];
			}
			for(int i=0; i<n; i++) {
				c[i] = W;
				p[i] = -1;
			}
			DFSVisit(v);
			int *r = new int[n];
			for(int i=0; i<n; i++) if(c[i]==B) r[i]=B;
			int **F = M;
			M = T;
			for(int i=0; i<n; i++) {
				c[i] = W;
				p[i] = -1;
			}
			DFSVisit(v);
			M = F;
			for(int i=0; i<n; i++) if(r[i]==B && c[i]==B) cout << i << " ";
			cout << endl;
		}
		
		void print_scc() {
			for(int i=0; i<n; i++) {
				if(r[i]>=0) {
					int root = r[i];
					cout << "{ ";
					for(int j=i; j<n; j++) {
						if(r[j]==root) {
							cout << j << " ";
							r[j] = -1;
						}
					}
					cout << "} ";
				}
			}
			cout << endl;
		}

		void print_scc2() {
			int *s = new int[n];
			for(int i=0; i<n; i++) s[i] = i;
			sort(s,n,r);
			int i = 0;
			while(i<n) {
				cout << "{ ";
				int root = r[s[i]];
				while(i<n && r[s[i]]==root) {
					cout << s[i] << " ";
					i++;
				}
				cout << "} ";
			}
			cout << endl;
		}
		
		void SCC() {
			DFS();
			int *s = new int[n];
			for(int i=0; i<n; i++) s[i] = i;
			sort(s,n,f);
			int **T;
			T = new int*[n];
			for(int i=0; i<n; i++) {
				T[i] = new int[n];
				for(int j=0; j<n; j++)
					T[i][j] = M[j][i];
			}
			int **F = M;
			M = T;
			for(int i=0; i<n; i++) {
				c[i] = W;
				p[i] = -1;
			}
			for(int i=0; i<n; i++)
				if( c[s[i]]==W ) {
					current_root = s[i];
					DFSVisit(s[i]);
				}
			print_scc2();
		}
};


template <class H> class LGraph {
	private:
		int *c, *p, *d, *f;
		int len, n, m;
		int t;
		H **K;
		LinkedList<int> **Adj;

		int findIndex(H x) {
			for(int i=0; i<n; i++)
				if(*K[i] == x) return i;
			return -1;
		}
	
	public:
		LGraph(int len) {
			this->len = len;
			n = m = 0;
			K = new H*[len];
			c = new int[len];
			p = new int[len];
			d = new int[len];
			f = new int[len];
			for(int i=0; i<len; i++) K[i] = NULL;
			Adj = new LinkedList<int>*[len];
			for(int i=0; i<len; i++) 
				Adj[i] = new LinkedList<int>();
		}

		LGraph<H>* addNode(H k) {
			if(n==len) return this;
			if(findIndex(k)>=0) return this;
			K[n] = new H(k);
			n++;
			return this;
		}
		
		LGraph<H>* addEdge(H x, H y) {
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
			for(int i=0; i<n; i++) {
				cout << "(" << i << ", " << *K[i] << ")" << " : ";
				Adj[i]->print();
				cout << endl;
			}
		}		
		

};



int main() {
	MGraph<char> *Gr = new MGraph<char>(9);
	Gr->addNode('0')->addNode('1')->addNode('2')->addNode('3');
	Gr->addNode('4')->addNode('5')->addNode('6')->addNode('7');
	Gr->addNode('8');
	
	Gr->addEdge('0','8')->addEdge('0','1');
	Gr->addEdge('1','8');
	Gr->addEdge('2','4');
	Gr->addEdge('3','5')->addEdge('3','6')->addEdge('3','7');
	Gr->addEdge('4','3')->addEdge('4','0');
	Gr->addEdge('5','6')->addEdge('5','3');
	Gr->addEdge('6','5');
	Gr->addEdge('8','2');
	Gr->print();
	Gr->SCC();
		
	
}
