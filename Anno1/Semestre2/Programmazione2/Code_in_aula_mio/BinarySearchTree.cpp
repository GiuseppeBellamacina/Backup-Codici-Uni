// Binary Search Tree
/*
Definire una classe BST che implementi:
- inserimento
- visite (inOrder, preOrder e postOrder)
*/
#include <iostream>
using namespace std;

class Nodo{
	public:
		int val;
		Nodo* left;
		Nodo* right;
		// facoltativo
		Nodo* parent;
		Nodo(Nodo* p, int v): left(NULL), right(NULL), parent(p), val(v) {}
};

class BST{
	private:
		Nodo* root;
		int numElem = 0;
		void inOrder(Nodo* p)const;
		void preOrder(Nodo* p)const;
		void postOrder(Nodo* p)const;
	public:
		BST(): root(NULL) {};
		void insert(int valore);
		void inOrder()const;
		void preOrder()const;
		void postOrder()const;
};

void BST::insert(int valore){
	Nodo* x = this->root;
	Nodo* y = NULL;
	while(x!=NULL){
		y = x;
		if(valore < x->val) x = x->left;
		else x = x->right;
	}
	Nodo* z = new Nodo(y,valore);
	if(y==NULL) this->root = z;
	else if(z->val<y->val) y->left = z;
	else y->right = z;
}

void BST::inOrder(Nodo* p)const{
	if(p){
		inOrder(p->left);
		cout << p->val << endl;
		inOrder(p->right);
	}
}

void BST::preOrder(Nodo* p)const{
	if(p){
		cout << p->val << endl;
		preOrder(p->left);
		preOrder(p->right);
	}
}

void BST::postOrder(Nodo* p)const{
	if(p){
		inOrder(p->left);
		inOrder(p->right);
		cout << p->val << endl;
	}
}

// versione pubblica
void BST::inOrder()const {inOrder(root);}
void BST::preOrder()const {preOrder(root);}
void BST::postOrder()const {postOrder(root);}


int main(){
	BST tree;
	tree.insert(5);
	tree.insert(3);
	tree.insert(8);
	tree.insert(19);
	tree.insert(2);
	tree.insert(11);
	
	cout << "inOrder:" << endl;
	tree.inOrder();
	cout << endl;
	cout << "preOrder:" << endl;
	tree.preOrder();
	cout << endl;
	cout << "postOrder:" << endl;
	tree.postOrder();
	return 0;
}
