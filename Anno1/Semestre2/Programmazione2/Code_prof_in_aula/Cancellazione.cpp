#include <iostream>
using namespace std;

class Boh{
	int x;
	public:
		Boh(){};
		Boh(int x){
			this->x = x;
		}
		
		int getX(){
			return x;
		}
		
		bool operator<(Boh& b){
			return x < b.x;
		}
		
		friend
		ostream& operator<<(ostream& os, const Boh& b){
			return os << b.x;
		}
};

class Nodo{
	public:
		Boh val;
		Nodo* parent;
		Nodo* left;
		Nodo* right;
};

class BST{
	private:
		Nodo* root;
	
	public:
		BST(){root = nullptr;}
		void insert(Boh valore);
		void inOrder()const;
		void inOrder(Nodo* p)const;
		int altezza(Nodo* p)const;
		bool cancella(Boh x);
		Nodo* ricerca(Boh x);
		void cancella(Nodo *);
    	void trapianta(Nodo* u, Nodo* v);
    	Nodo* minimo(Nodo* x);
    	Boh minimo();
    	Nodo* getRoot(){
    		return root;
		}
    	
    	void inOrder(Nodo* p, Boh* a){
    		static int zz;
	    	if(p!=nullptr){
		        inOrder(p->left,a);
		        a[zz++] = p->val;
		        inOrder(p->right,a);
		    }	
		}
		
		friend
    	ostream& operator<<(ostream& out, const BST& t);
		
};

void stampaLivello(Nodo* p, int level){ // stampa i nodi ad un dato livello
    // p punta ad una posizione vuota
    if(p == nullptr){
        if (level==0) cout << "_\t";
        return;
    }

    if(level == 0)
       cout << p->val.getX() << "\t";
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

Nodo* BST::ricerca(Boh x){
	Nodo* p = root;
	while((p != nullptr) && (p->val.getX() != x.getX())){
		if(x < p->val) p = p->left;
		else p = p->right;
	}
	return p;
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

Boh BST::minimo(){
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


bool BST::cancella(Boh x){
    cancella(ricerca(x));
    return true;
}

void BST::insert(Boh valore){

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
}

int main(){
	Boh a(4);
	Boh b(5);
	Boh c(7);
	Boh d(1);
	
	BST tree;
	tree.insert(a);
	tree.insert(b);
	tree.insert(c);
	tree.insert(d);
	cout << tree << endl;
	
	Boh arr[4];
	int zz = 0;
	tree.inOrder(tree.getRoot(), arr);
	
	for(int i=0; i<4 && arr[i].getX()<5; i++){
		tree.cancella(arr[i]);
	}
	cout << tree;
	
	
	
	return 0;
}
