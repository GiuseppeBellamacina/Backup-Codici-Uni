#include <iostream>
#include <ctime>
#include <math.h>
using namespace std;

template <class T> class Node {
	private:
		T key;
		Node<T> *left, *right, *parent;
		int color;
		int leaf;
		
	public:
		Node<T>(T key) {
			this->key = key;
			left = right = parent = NULL;
			leaf = 1;
		}
		
		T getKey() {return key;}
		int getColor() {return color;}
		int isLeaf() {return leaf;}
		Node<T>* getLeft() {return left;}
		Node<T>* getRight() {return right;}
		Node<T>* getParent() {return parent;}
		void setKey(T key) {this->key = key;}
		void setColor(int color) {this->color = color;}
		void setLeaf(int leaf) {this->leaf = leaf;}
		void setLeft(Node<T>* left) {this->left = left;}
		void setRight(Node<T>* right) {this->right = right;}
		void setParent(Node<T>* parent) {this->parent = parent;}
};

template <class T> class BSTree {
	private:
		Node<T> *root;
		int size;
		
		void inorder_visit(Node<T>* n) {
			if(n!=NULL) {
				inorder_visit(n->getLeft());
				cout << n->getKey() << " ";
				inorder_visit(n->getRight());
			}
		}

		void postorder_visit(Node<T>* n) {
			if(n!=NULL) {
				postorder_visit(n->getLeft());
				postorder_visit(n->getRight());
				cout << n->getKey() << " ";
			}
		}

		void preorder_visit(Node<T>* n) {
			if(n!=NULL) {
				cout << n->getKey() << " ";
				preorder_visit(n->getLeft());
				preorder_visit(n->getRight());
			}
		}

	
	protected: 
		Node<T> *search(T key) {
			Node<T> *tmp = root;
			while(tmp!=NULL && tmp->getKey()!=key) {
				if(key>tmp->getKey())
					tmp = tmp->getRight();
				else tmp = tmp->getLeft();
			}
			return tmp;
		}
		Node<T>* getRoot() {return root;}

		BSTree<T> *rightRotate(Node<T> *y) {
			Node<T> *x = y->getLeft();
			Node<T> *z = y->getParent();
			y->setLeft(x->getRight());
			x->setRight(y);
			if(z!=NULL) {
				if(y==z->getLeft()) z->setLeft(x);
				else z->setRight(x);
			}
			else root = x;
			x->setParent(z);
			y->setParent(x);
			if(y->getLeft()) y->getLeft()->setParent(y);
			return this;
		}

		BSTree<T> *leftRotate(Node<T> *y) {
			Node<T> *x = y->getRight();
			Node<T> *z = y->getParent();
			y->setRight(x->getLeft());
			x->setLeft(y);
			if(z!=NULL) {
				if(y==z->getRight()) z->setRight(x);
				else z->setLeft(x);
			}
			else root = x;
			x->setParent(z);
			y->setParent(x);
			if(y->getRight()) y->getRight()->setParent(y);
			return this;
		}
		
		Node<T>* minimum(Node<T>* n) {
			if(n==NULL) return n;
			Node<T>* tmp = n;
			while(tmp->getLeft())
				tmp = tmp->getLeft();
			return tmp;
		}

		Node<T>* maximum(Node<T>* n) {
			if(n==NULL) return n;
			Node<T>* tmp = n;
			while(tmp->getRight())
				tmp = tmp->getRight();
			return tmp;
		}
		
		Node<T>* predecessor(Node<T> *n) {
			if(n==NULL) return n;
			if(n->getLeft()) return maximum(n->getLeft());
			Node<T>* tmp = n->getParent();
			while(tmp!=NULL && n == tmp->getLeft()) {
				n = tmp;
				tmp = tmp->getParent();
			}			
			return tmp;
		}

		Node<T>* successor(Node<T> *n) {
			if(n==NULL) return n;
			if(n->getRight()) return minimum(n->getRight());
			Node<T>* tmp = n->getParent();
			while(tmp!=NULL && n == tmp->getRight()) {
				n = tmp;
				tmp = tmp->getParent();
			}			
			return tmp;
		}

		Node<T> *delete_node(T key) {
			Node<T> *n = search(key);
			if(!n) return NULL;
			Node<T> *p = n->getParent();
			// n non ha figlio sinistro
			if(n->getLeft()==NULL) {
				if(p) {
					if(n == p->getLeft()) p->setLeft(n->getRight());
					else p->setRight(n->getRight());
				}
				else root = n->getRight();
				if( n->getRight() ) n->getRight()->setParent(p);
				return n;
			}
			// n ha figlio sinistro ma non figlio destro
			if(n->getRight()==NULL) {
				if(p) {
					if(n == p->getLeft()) p->setLeft(n->getLeft());
					else p->setRight(n->getLeft());
				}
				else root = n->getLeft();
				n->getLeft()->setParent(p);
				return n;
			}
			// n ha entrambi i figli
			Node<T> *s = successor(n); 
			del(s->getKey());
			n->setKey(s->getKey());
			return s;
		}
		
	public:
		BSTree<T>() {
			root = NULL;
			size = 0;
		}
		int getSize() {return size;}
		
		BSTree<T> *insert(T key) {
			Node<T>* tmp = root;
			Node<T>* parent = NULL;
			while(tmp!=NULL) {
				parent = tmp;
				if(key>tmp->getKey()) {
					tmp = tmp->getRight();
				}
				else tmp = tmp->getLeft();
			}
			Node<T> *n = new Node<T>(key);
			if(parent==NULL) root = n;
			else {
				n->setParent(parent);
				if(key>parent->getKey()) {
					parent->setRight(n);
				}
				else parent->setLeft(n);
				parent->setLeaf(0);
			}
			size++;
			return this;
		}

		BSTree<T> *del(T key) {
			delete_node(key);
			return this;
		}
		
		BSTree<T> *rightRotate(T key) {
			Node<T> *n = search(key);
			if(n!=NULL) rightRotate(n);
			return this;
		}

		BSTree<T> *leftRotate(T key) {
			Node<T> *n = search(key);
			if(n!=NULL) leftRotate(n);
			return this;
		}
		
		void inorder() { inorder_visit(root); cout << endl; }
		void postorder() { postorder_visit(root); cout << endl; }
		void preorder() { preorder_visit(root); cout << endl; }

};
