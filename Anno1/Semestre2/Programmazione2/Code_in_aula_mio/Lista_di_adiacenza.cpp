#include <iostream>
using namespace std;

template <class T> struct Nodo{
	T valore;
	Nodo<T>* succ;
};

template <class T> class Lista{
	public:
		Lista() {testa = NULL;}
		void print();
		void insert(T val);
		Nodo<T>* getTesta() {return testa;}
		Nodo<T>* search(T val);
	private:
		Nodo<T>* testa;
	
	friend ostream& operator<<(ostream& out; const Lista l);
};
