#include <iostream>
#include <ctime>
#include <math.h>
#include <string.h>
using namespace std;
#define MAX 256

template <class T> class Node {
	private:
		T key;
		int value;
		Node<T> *left, *right;
		int leaf;
	public:
		Node<T>(T key) {
			this->key = key;
			left = right = NULL;
			leaf = 1;
		}
		T getKey() {return key;}
		int isLeaf() {return leaf;}
		int getValue() {return value;}
		Node<T>* getLeft() {return left;}
		Node<T>* getRight() {return right;}
		void setKey(T key) {this->key = key;}
		void setLeaf(int leaf) {this->leaf = leaf;}
		void setValue(int value) {this->value = value;}
		void incValue() {this->value++;}
		void setLeft(Node<T>* left) {this->left = left;}
		void setRight(Node<T>* right) {this->right = right;}
};

template <class T> class BinaryTree {
	private:
		int size;
		Node<T> *root;
	public:
		BinaryTree<T>(T x) {
			root = new Node<T>(x);
			size = 1;
		}
		BinaryTree<T>(BinaryTree<T> *a, BinaryTree<T> *b, T x) {
			root = new Node<T>(x);
			size = a->getSize() + b->getSize() + 1;		
			root->setLeft(a->getRoot());
			root->setRight(b->getRoot());
			root->setLeaf(0);
		}
		int getSize() {return size;}
		Node<T>* getRoot() {return root;}
};

class Code {
	private:
		int c;
		int len;
	public:
		Code(int len) {
			c = 0;
			this->len = len;
		}
		Code(int len, int mask) {
			c = mask;
			this->len = len;
		}
		void setBit(int i) {
			int mask = 1 << i;
			c = c|mask;
		}
		void unsetBit(int i) {
			int mask = 1 << i;
			mask = ~mask;
			c = c & mask; 
		}
		int getBit(int i) {
			int mask = 1;
			return (c>>i)&mask;
		}
		void print() {
			for(int i=0; i<len; i++)
				cout << getBit(i);
			cout << endl;
		}
};

class Huffman {
	private:
		BinaryTree<char> *T;
		Code *HT[MAX];
		int alpha;
		
		int getFreq(BinaryTree<char> *t) {
			if(t==NULL) return 0;
			return t->getRoot()->getValue();
		}
		
		void reverseOrder(BinaryTree<char> *S[], int n) {
			for(int i=1; i<n; i++) {
				int j = i;
				while(j>0 && getFreq(S[j])>getFreq(S[j-1])) {
					BinaryTree<char> *temp = S[j];
					S[j] = S[j-1];
					S[j-1] = temp;
					j--;
				}
			}
		}
		
		BinaryTree<char> *computeHuffmanTree(char *text, int n) {
			int freq[MAX];
			for(int i=0; i<MAX; i++) freq[i] = 0;
			alpha = 0;
			for(int i=0; i<n; i++) {
				if(freq[text[i]]==0) {
					alpha++;
				}
				freq[text[i]]++;
			}
			
			BinaryTree<char> *TreeSet[MAX];
			for(int i=0; i<MAX; i++) TreeSet[i] = NULL;
			int j = 0;
			for(int i=0; i<MAX; i++)
				if(freq[i]>0) {
					TreeSet[j] = new BinaryTree<char>((char)i);
					TreeSet[j]->getRoot()->setValue(freq[i]);
					j++;
				}
			
			reverseOrder(TreeSet, alpha);
			j = alpha-1;
			while(j>0) {
				BinaryTree<char> *a = TreeSet[j-1];
				BinaryTree<char> *b = TreeSet[j];
				BinaryTree<char> *c = new BinaryTree<char>(a,b,'@');
				c->getRoot()->setValue(getFreq(a)+getFreq(b));
				TreeSet[j-1] = c;
				TreeSet[j] = NULL;
				int k = j-1;
				while(k>0 && getFreq(TreeSet[k])>getFreq(TreeSet[k-1])) {
					BinaryTree<char> *temp = TreeSet[k];
					TreeSet[k] = TreeSet[k-1];
					TreeSet[k-1] = temp;
					k--;
				}
				j--;
			}
			
			for(int i = 0; i<alpha; i++)
				if(TreeSet[i]!=NULL) 
					cout << TreeSet[i]->getRoot()->getKey() << ": " << getFreq(TreeSet[i]) <<endl;

			return TreeSet[0];
		}

		void visitTree(Node<char>* t, int mask, int len) {
			if(t==NULL) return;
			//cout << t->getKey() << endl;
			if(t->isLeaf()) {
				HT[t->getKey()] = new Code(len, mask);
				return;
			}
			visitTree(t->getLeft(), mask, len+1);
			mask = mask | (1<<(len));
			visitTree(t->getRight(), mask, len+1);
		}
		
	public:
		Huffman(char *text, int n) {
			for(int i=0; i<MAX; i++) HT[i] = NULL;
			T = computeHuffmanTree(text, n);
			int mask = 0;
			visitTree(T->getRoot(), mask, 0);
		}
		
		void printHT() {
			for(int i=0; i<MAX; i++) {
				if(HT[i]!=NULL) {
					cout << (char)i << ": ";
					HT[i]->print();
				}
			}
		}
};


int main() {
	char prova[] = "questo rappresenta un testo di prova";
	int n = strlen(prova);
	Huffman *H = new Huffman(prova,n);
	H->printHT();
	return 1;
}
