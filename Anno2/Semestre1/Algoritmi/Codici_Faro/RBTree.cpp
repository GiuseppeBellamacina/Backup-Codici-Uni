#include <iostream>
#include <ctime>
#include <math.h>
#include "BSTree.cpp"
using namespace std;

template <class H> class RBTree : public BSTree<H> {
	private:
		static const int BLACK = 0;
		static const int RED = 1;
		static const int BLACKBLACK = 2;

		void inorder_visit(Node<H>* n) {
			if(n!=NULL) {
				inorder_visit(n->getLeft());
				cout << "(" << n->getKey() << ", " << printC(n->getColor()) << ") ";
				inorder_visit(n->getRight());
			}
		}

		void postorder_visit(Node<H>* n) {
			if(n!=NULL) {
				postorder_visit(n->getLeft());
				postorder_visit(n->getRight());
				cout << "(" << n->getKey() << ", " << printC(n->getColor()) << ") ";
			}
		}

		void preorder_visit(Node<H>* n) {
			if(n!=NULL) {
				cout << "(" << n->getKey() << ", " << printC(n->getColor()) << ") ";
				preorder_visit(n->getLeft());
				preorder_visit(n->getRight());
			}
		}
		
		char printC(int color) {
			if(color==0) return 'B';
			if(color==1) return 'R';
			return 'X';
		}
		
		void RBInsertFixup(Node<H> *z) {
			if(z->getParent()!=NULL && z->getParent()->getColor()==BLACK) return;
			if(z == this->getRoot()) {
				z->setColor(BLACK);
				return;
			}
			Node<H> *padre = z->getParent();
			Node<H> *nonno = padre->getParent();
			Node<H> *zio = nonno->getRight();
			if(padre == nonno->getRight()) zio = nonno->getLeft();
			if(zio!=NULL && zio->getColor() == RED) {
				// caso 1
				zio->setColor(BLACK);
				padre->setColor(BLACK);
				nonno->setColor(RED);
				RBInsertFixup(nonno);
				return;
			}
			if(padre == nonno->getLeft()) {
				if(z == padre->getRight()) {
					// caso 3
					this->leftRotate(padre);
					padre = z;
					z = padre->getLeft();
				}
				// caso 2
				this->rightRotate(nonno);
				padre->setColor(BLACK);
				nonno->setColor(RED);
				return;
			}
			else { // casi simmetrici ai precedenti
				if(z == padre->getLeft()) {
					// caso 3
					this->rightRotate(padre);
					padre = z;
					z = padre->getRight();
				}
				// caso 2
				padre->setColor(BLACK);
				nonno->setColor(RED);
				this->leftRotate(nonno);
				return;
			}
		}
		
		void swapColor(Node<H> *x, Node<H> *y) {
			int tmp = x->getColor();
			x->setColor(y->getColor());
			y->setColor(tmp);
		}

			
	public:
		RBTree<H>() : BSTree<H>() {}
		RBTree<H> *insert(H key) {
			BSTree<H>::insert(key);
			Node<H> *n = this->search(key);
			n->setColor(RED);
			RBInsertFixup(n);
			return this;
		}
		
		void inorder() { inorder_visit(this->getRoot()); cout << endl; }
		void postorder() { postorder_visit(this->getRoot()); cout << endl; }
		void preorder() { preorder_visit(this->getRoot()); cout << endl; }
};

int main() {
	RBTree<int> *t = new RBTree<int>();
	t->insert(9)->insert(22)->insert(25)->insert(15)->insert(23)->insert(13)->insert(2)->insert(14)->insert(24)->insert(1);
	t->inorder();
	t->postorder();
}
