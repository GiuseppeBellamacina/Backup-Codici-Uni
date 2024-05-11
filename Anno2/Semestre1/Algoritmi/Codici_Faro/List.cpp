#include <iostream>
#include <ctime>
#include <math.h>
using namespace std;

template <class T> class List {
	public:
		virtual List<T>* insert(T x) = 0;
		virtual List<T>* del(T x) = 0;
		virtual int search(T x) = 0;
};

template <class C> class Node {
	private:
		C key;
		Node<C> *next;
	public:
		Node<C>(C key) {
			this->key = key;
			this->next = NULL;
		}
		void setKey(C key) {
			this->key = key;
		}
		void setNext(Node<C> *next) {
			this->next = next;
		}
		C getKey() {
			return key;
		}
		Node<C>* getNext() {
			return next;
		}
};


template <class H> class LinkedList : public List<H>{
	private:
		Node<H> *root;
		int size;
	public:
		LinkedList<H>() {
			root = NULL;
			size = 0;
		}

		LinkedList<H>* insert(H x) {
			Node<H> *tmp = new Node<H>(x);
			tmp->setNext(root);
			root = tmp;
			size++;
			return this;
		}

		LinkedList<H>* del(H x) {
			Node<H> *tmp = root;
			Node<H> *par = NULL;
			while(tmp!=NULL && tmp->getKey()!=x) {
				par = tmp;
				tmp=tmp->getNext();
			}
			if(tmp!=NULL) par->setNext(tmp->getNext());
			size--;
			free(tmp);
			return this;
		}

		int search(H x) {
			Node<H> *tmp = root;
			while(tmp!=NULL && tmp->getKey()!=x) tmp=tmp->getNext();
			return tmp!=NULL?1:0;
		}
		
		void print() {
			Node<H> *tmp = root;
			while(tmp!=NULL) {
				cout << tmp->getKey() << " - ";
				tmp = tmp->getNext();
			}
			cout << "//";
		}
};
