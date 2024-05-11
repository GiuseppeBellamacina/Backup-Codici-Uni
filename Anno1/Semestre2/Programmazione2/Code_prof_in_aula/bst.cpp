
/*
Definire una classe BST che implementi:
- inserimento
- visite (inorder, preorder e postorder)
*/
#include <iostream>
using namespace std;

class Nodo {
    int val;
    Nodo* left;
    Nodo* right;
    //facoltativo
    Nodo* parent;
};


class BST{
public:
    BST(): root(nullptr){};
    void insert(int valore);
    void inOrder()const; // sx rad dx
    void preOrder()const;// rad sx dx
    void postOrder()const;// sx dx rad

    //facoltative:
    // operator<<
    // int altezza(Nodo* p)const;

private:
    Nodo* root;
    int numElem =0;
    void inOrder(Nodo* p)const;
    void preOrder(Nodo* p)const;
    void postOrder(Nodo* p)const;
};

//versione pubblica
void BST::inOrder() const {inOrder(root);}


// void stampaLivello(Nodo* p, int level); // stampa i nodi ad un dato livello
//NB: questa puo' essere sfruttata da operator<<

int main(){
    BST tree;
    tree.insert(6);
    tree.insert(5);
    tree.insert(7);
    tree.insert(2);
    tree.insert(8);
    tree.insert(4);

    cout << tree << endl;

    cout << "Visita preorder:";
    tree.preOrder();

    cout << "Visita inorder:";
    tree.inOrder();

    cout << "Visita postorder:";
    tree.postOrder();

    return 0;
}
