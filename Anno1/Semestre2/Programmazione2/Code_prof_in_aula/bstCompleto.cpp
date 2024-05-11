
/*
Definire una classe BST che implementi:
- inserimento
- visite (inorder, preorder e postorder)
- cancellazione di un nodo
*/
#include <iostream>
using namespace std;

class Nodo {
public:
    int val;
    Nodo* left;
    Nodo* right;
    Nodo* parent;
};


class BST{
public:
    BST(): root(nullptr){};
    BST(Nodo* r) {
    	root = r;
	}
    void insert(int valore);
    void inOrder()const; // sx rad dx
    void preOrder()const;// rad sx dx
    void postOrder()const;// sx dx rad

    int altezza(Nodo* p)const;
    Nodo* getRoot() {return root;}

	Nodo* invertTree(Nodo* root);
    bool cancella(int x);
    int minimo();
    Nodo* ricerca(int x);
    int successore(int n);
    Nodo* successoretdm(Nodo* p);

    friend
    ostream& operator<<(ostream& out, const BST& t);

private:
    Nodo* root;
    int numElem =0;
    void inOrder(Nodo* p)const;
    void preOrder(Nodo* p)const;
    void postOrder(Nodo* p)const;

    //procedure ausiliarie per la cancellazione
    void cancella(Nodo *);
    void trapianta(Nodo* u, Nodo* v);
    Nodo* minimo(Nodo* x);

};

Nodo* BST::invertTree(Nodo* root){
	if(root != nullptr){
		Nodo* aux = root->left;
		root->left = root->right;
		root->right = aux;
		
		root->left = invertTree(root->left);
		root->right = invertTree(root->right);	
	}
	return root;
}

Nodo* BST::ricerca(int x){
	Nodo* p = root;
	while((p != nullptr) && (p->val != x)){
		if(x < p->val) p = p->left;
		else p = p->right;
	}
	return p;
}

int BST::successore(int n){
	Nodo* x = ricerca(n);
	if(x->right != nullptr) return minimo(x->right)->val;
	Nodo* y = x->parent;
	while((y != nullptr) && (x == y->right)){
		x = y;
		y = y->parent;
	}
	return y->val;
}


void BST::inOrder(Nodo* p) const{
    if(p!=nullptr){
        inOrder(p->left);
        cout << p->val << "\t";
        inOrder(p->right);
    }
}
//versione pubblica
void BST::inOrder() const {inOrder(root);}


void BST::preOrder(Nodo* p) const{
    if(p!=nullptr){
        cout << p->val << "\t";
        preOrder(p->left);
        preOrder(p->right);
    }
}
//versione pubblica
void BST::preOrder()const {preOrder(root);}



void BST::postOrder(Nodo* p) const{
    if(p!=nullptr){
        postOrder(p->left);
        postOrder(p->right);
        cout << p->val << "\t";
    }
}
//versione pubblica
void BST::postOrder()const {postOrder(root);}

void BST::insert(int valore){

    Nodo* nuovo = new Nodo;
    Nodo* x = root, *y = nullptr;

    nuovo->val = valore;
    nuovo->left = nuovo->right = nullptr;

    while(x!=nullptr){
        y=x;
        if(valore< x->val)
            x = x->left;
        else
            x = x->right;
    }

    nuovo->parent = y;
    if(y==nullptr)
        root = nuovo;
    else if(valore<y->val)
        y->left = nuovo;
    else
        y->right = nuovo;

    numElem++;
}

//NB: questa puo' essere sfruttata da operator<<
void stampaLivello(Nodo* p, int level){ // stampa i nodi ad un dato livello
    // p punta ad una posizione vuota
    if(p == nullptr){
        if (level==0) cout << "_\t";
        return;
    }

    if(level == 0)
       cout << p->val << "\t";
    else if(level>0){
        stampaLivello(p->left,level-1);
        stampaLivello(p->right,level-1);
    }

}

int BST::altezza(Nodo* p)const{
    if (p==nullptr) return 0;

    int lh = altezza(p->left);
    int rh = altezza(p->right);

    if(lh>rh)   return (lh+1);
    else        return (rh+1);
}


ostream& operator<<(ostream&out, const BST& t){
    int h = t.altezza(t.root);
    cout << "Albero di altezza " << h << endl;
    for(int i=0;i<h;i++){
        stampaLivello(t.root, i);
        cout << endl;
    }
    return out;
}

void BST::trapianta(Nodo* u, Nodo* v){

    if(u->parent == nullptr) // se u e' la radice
        root = v;
    else if (u == u->parent->left) // se u e' figlio sx di suo padre
        u->parent->left = v;
    else
        u->parent->right = v;
    if(v!=nullptr)
        v->parent = u->parent;
}

int BST::minimo(){
    Nodo* nMin = minimo(root);
    return nMin->val;
}

Nodo* BST::minimo(Nodo* x){
    //bisognerebbe controllare che x!=nullptr
    Nodo* nMin =x;
    while(nMin->left != nullptr)
        nMin = nMin->left;
    return nMin;
}

void BST::cancella(Nodo* z){
    Nodo* y;
    //Caso 1: z ha un solo figlio
    if(z->left == nullptr)
        trapianta(z, z->right); // z non ha figlio sx
    else if(z->right == nullptr)
        trapianta(z, z->left); // z non ha figlio dx
    // altrimenti... caso 3: z ha entrambi i figli
    else{
        y = minimo(z->right); // y sara' il successore di z
        // se y non e' figlio di z devo gestire y.right e z.right
        if(y->parent!=z){ // caso 3 generale
            trapianta(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        trapianta(z,y);
        y->left = z->left;
        y->left->parent = y;
    }
    delete z;
}


bool BST::cancella(int x){
    Nodo* iter = root;
    // ricerca di un nodo con chiave x
    while((iter!=nullptr) && (x!=iter->val)){
        if(x< iter->val)
            iter = iter->left;
        else
            iter = iter->right;
    }
    if(iter == nullptr)
        return false;
    // chiamo la procedura privata
    cancella(iter);
    return true;
}

Nodo* BST:: successoretdm(Nodo* p){
       if(p->right!=NULL) //se il nodo ha una parte destra ovviamente il successore si trova l�
       return minimo(p->right); //e sar� il minimo della parte destra

       //caso generale: il successore � un antenato di p
       Nodo* y=p->parent; //in y ci sar� alla fine il successore
                          //ma all'inizio sar� per tenere conto il padre di p

       while(y!=NULL && p==y->right) {//risali fino a che non vedi un nodo(p) che � un figlio sinistro
       p=y;                           //questo perch� y poi avr� una parte destra con nodi maggiori di y stesso
       y=y->parent; //risaliamo l'albero fino a trovatr un figlio sinistro di suo padre
       }
       return y;
}

int main(){
    BST tree;
    tree.insert(6);
    tree.insert(5);
    tree.insert(7);
    tree.insert(2);
    tree.insert(8);
    tree.insert(4);
    
    cout << tree.successoretdm(tree.ricerca(7))->val << endl;
    

    cout << tree << endl;
    BST tree2(tree.invertTree(tree.getRoot()));
    cout << tree2 << endl;
    tree.invertTree(tree.getRoot());
    cout << tree << endl;
    
    cout << "Il successore e' " << tree.successore(4) << endl << endl;


    cout << "Visita inorder:\t\t";
    tree.inOrder();
    cout << endl;
    cout << "Visita preorder:\t";
    tree.preOrder();
    cout << endl;
    cout << "Visita postorder:\t";
    tree.postOrder();

    int v = 7;
    cout << endl << "Cancello il nodo con chiave " << v << endl;
    if(!tree.cancella(v))
        cout << "Elemento non trovato nell'albero." << endl;

    cout << endl << tree << endl;

    // albero pieno e bilanciato
    BST tree1;
    tree1.insert(8);
    tree1.insert(5);
    tree1.insert(18);
    tree1.insert(2);
    tree1.insert(6);
    tree1.insert(19);
    tree1.insert(16);

    cout << tree1 << endl;

    tree1.cancella(18);
    cout << tree1;
    return 0;
}
