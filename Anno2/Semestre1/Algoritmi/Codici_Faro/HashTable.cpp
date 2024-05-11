#include <iostream>
#include <ctime>
#include <math.h>
#include "List.cpp"
using namespace std;

template <class T> class HashTable {
	public:
		virtual HashTable<T>* insert(T x) = 0;
		virtual int search(T x) = 0;
		virtual HashTable<T>* del(T x) = 0;
};

template <class H> class LinkedHashTable : public HashTable<H> {
	private:
		virtual int hash(H x) = 0;
		int m;
		int size;
		LinkedList<H> **t;
		
	public:
		LinkedHashTable<H>(int m) {
			t = new LinkedList<H>*[m];
			for(int i=0; i<m; i++) t[i] = new LinkedList<H>();
			this->size = 0;
			this->m = m;
		}
		
		int getm() {return m;}
		void setm(int m) {this->m = m;}
		int getSize() {return size;}
		//void setSize(int size) {this->size = size;}
		
		LinkedHashTable<H>* insert(H x) {
			int p = hash(x);
			t[p]->insert(x);
			size++;
			return this;
		}
		
		int search(H x) {
			int p = hash(x);
			return t[p]->search(x);
		}
		
		LinkedHashTable<H>* del(H x) {
			int p = hash(x);
			if(t[p]->search(x)) {
				t[p]->del(x);
				size--;
			}
			return this;
		}
		
		void print() {
			for(int i=0; i<m; i++) {
				cout << "[" << i << "] -> ";
				t[i]->print();
				cout << endl;
			}
			cout << endl;
		}
};


template <class H> class DivLinkedHashTable : public LinkedHashTable<H> {
	private:
		int hash(H x) {
			int h = ((int)x % this->getm());
			return h;
		}
	public:
		DivLinkedHashTable(int m) : LinkedHashTable<H>(m) {}
};

template <class H> class MulLinkedHashTable : public LinkedHashTable<H> {
	private:
		double c;
		int hash(H x) {
			double y = (int)x * c;
			double a = y - (int)y; 
			int h = a * this->getm();
			return h;
		}
	public:
		MulLinkedHashTable(int m) : LinkedHashTable<H>(m) {
			c = 0.7;
		}
};


template <class H> class OpenHashTable : public HashTable<H> {
	private:
		virtual int hash(H x, int i) = 0;
		int m;
		int size;
		H **t;
		H *deleted;
		
	public:
		OpenHashTable<H>(int m) {
			t = new H*[m];
			for(int i=0; i<m; i++) t[i] = NULL;
			this->size = 0;
			this->m = m;
			deleted = new H();
		}
		
		int getm() {return m;}
		void setm(int m) {this->m = m;}
		int getSize() {return size;}
		
		OpenHashTable<H>* insert(H x) {
			if(size==m) return this;
			int i=0;
			int p = hash(x,i);
			while(i<m && t[p]!=NULL && t[p]!=deleted) {
				i++;
				p = hash(x,i);
			}
			if(t[p]==NULL || t[p]==deleted) t[p] = new H(x);
			return this;
		}
		
		int search(H x) {
			int i=0;
			int p = hash(x,i);
			while(i<m && t[p]!=NULL) {
				if( t[p]!=deleted && *t[p]==x ) return 1;
				i++;
				p = hash(x,i);
			}
			return 0;
		}
		
		OpenHashTable<H>* del(H x) {
			int i=0;
			int p = hash(x,i);
			while(i<m && t[p]!=NULL) {
				if( *t[p]==x ) {
					t[p] = deleted;
					return this;
				}
				i++;
				p = hash(x,i);
			}
			return this;
		}
		
		void print() {
			for(int i=0; i<m; i++) {
				if(t[i] && t[i]!=deleted) cout << "[" << i << "] -> " << *t[i];
				else cout << "[" << i << "] -> //";
				cout << endl;
			}
			cout << endl;
		}
};

template <class H> class LinearOpenHashTable : public OpenHashTable<H> {
	private:
		int hash(H x, int i) {
			return (((int)x % this->getm()) + i) % this->getm();
		}
	public:
		LinearOpenHashTable(int m) : OpenHashTable<H>(m) {
		}
};


int main() {
	LinearOpenHashTable<int> *T1 = new LinearOpenHashTable<int>(11);
	T1->insert(4)->insert(34)->insert(31)->insert(56)->insert(51)->insert(44)->insert(33)->insert(77)->insert(50);
	T1->del(34)->del(77);
	T1->insert(77)->insert(22);
	T1->print();
	return 1;
}
