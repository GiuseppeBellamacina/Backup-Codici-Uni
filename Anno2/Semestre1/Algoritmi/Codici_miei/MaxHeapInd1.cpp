// QUESTA IMPLEMENTAZIONE RICHIEDE ARRAY CON INDICE INIZIALE 1
#include <iostream>
#include <cmath>

using namespace std;

template <typename T>
class MaxHeap{
    private:
        T* arr;
        int len;
        int heapsize;
    
    public:
        MaxHeap(int l) : len(l+1), heapsize(0){
            arr = new T[len];
        }

        void swap(T, T);
        int geth(){return heapsize;}
        T& get(int i){return arr[i];}

        int left(int);
        int right(int);
        int parent(int);

        void heapify(int);
        MaxHeap* insert(T);
        T extractMax(); // estrae la radice
        void increaseKey(int, T); // aumenta una chiave
        MaxHeap* insertAlt(T); // altro modo per effettuare un inserimento
        void buildMaxHeap(); // regolarizza un MaxHeap che non rispetta le proprieta'
        void buildMaxHeap(T*, int); // costruisce un MaxHeap da un array
        void heapSort(T*, int); // algoritmo di sorting

        // Stampa un MaxHeap sottoforma di array
        void print(){
            for(int i=1; i<=heapsize; i++) cout << arr[i] << '\t';
            cout << endl;
        }
        void printTree(); // stampa l'Heap come albero
};

// Scambia 2 nodi
template <typename T> void MaxHeap<T>::swap(T i, T j){
    T tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

// Ritorna l'indice del figlio sinistro
template <typename T> int MaxHeap<T>::left(int i){
    //return i << 1;
    return 2*i;
}

// Ritorna l'indice del figlio destro
template <typename T> int MaxHeap<T>::right(int i){
    //return (i<<1)||1;
    return 2*i+1;
}

// Ritorna l'indice del nodo padre
template <typename T> int MaxHeap<T>::parent(int i){
    //return i >> 1;
    return i/2;
}

// Elimina una violazione della proprieta' del MaxHeap
template <typename T> void MaxHeap<T>::heapify(int i){
    int max = i;
    int l = left(i);
    if(l<=heapsize && arr[l]>arr[max])  max = l;
    int r = right(i);
    if(r<=heapsize && arr[r]>arr[max])  max = r;
    if(max != i){
        swap(max, i);
        heapify(max); // si ripete ricorsivamente per eliminare le eventuali violazioni
    }
}

// Inserisce un elemento in un MaxHeap
template <typename T> MaxHeap<T>* MaxHeap<T>::insert(T k){
    arr[++heapsize] = k;
    int i = heapsize;
    while(i>1 && arr[parent(i)]<arr[i]){
        swap(i, parent(i));
        i = parent(i);
    }
    return this; // cosi' posso effettuare più inserimenti in un'unica riga
}

// Estrae il massimo di un MaxHeap
template <typename T> T MaxHeap<T>::extractMax(){
    if(heapsize<1){
        cerr << "Heap underflow" << endl;
        exit(-1);
    }
    swap(1, heapsize);
    heapsize--;
    heapify(1);
    return arr[heapsize+1];
}

// Modifica il valore del nodo selezionato di un MaxHeap
template <typename T> void MaxHeap<T>::increaseKey(int i, T k){
    arr[i] = k;
    while(i>1 && arr[parent(i)]<arr[i]){
        swap(i, parent(i));
        i = parent(i);
    }
}

// Altro metodo di inserimento analogo al primo
template <typename T> MaxHeap<T>* MaxHeap<T>::insertAlt(T k){
    arr[++heapsize] = 0;
    increaseKey(heapsize, k);
    return this;
}

// Regola l'ordine di un MaxHeap modificato
template <typename T> void MaxHeap<T>::buildMaxHeap(){
    for(int i=heapsize/2; i>=1; i--) heapify(i); // si effettua per il numero dei nodi non foglia
}

// Crea un MaxHeap da un array di input con dimensione n
template <typename T> void MaxHeap<T>::buildMaxHeap(T* A, int n){
    for(int i=1; i<=n; i++) insert(A[i]);
}

// Ordina gli elementi di un array di dimensione n in un MaxHeap
template <typename T> void MaxHeap<T>::heapSort(T* A, int n){
    buildMaxHeap(A,n);
    for(int i=n; i>=2; i--){
        swap(1,i);
        heapsize--;
        heapify(1);
    }
    heapsize = n;
}

// Stampa un MaxHeap sottoforma di albero completo
template <typename T> void MaxHeap<T>::printTree(){
    int num=heapsize;
    int nLevel;
    for(nLevel=0; num>0; nLevel++){
        num -= pow(2,nLevel);
    }
    int z=1;
    int tabCurr = pow(2,nLevel-1)-1, tabPrec = tabCurr;
    for(int i=0; i<nLevel; i++){
        for(int j=0; j<tabCurr; j++) cout << '\t';
        for(int j=0; j<pow(2,i); j++){
            if(z > heapsize) break;
            cout << '(' << arr[z++] << ')';
            for(int q=0; q<=tabPrec; q++) cout << '\t';
        }
        cout << endl;
        tabPrec = tabCurr;
        tabCurr/=2;
    }
    cout << endl;
}


int main(){
    MaxHeap<int> heap(20);
    MaxHeap<int> heap1(20);

    int A[20] = {0,9,4,6,5,2,12,0,14,25,110,15,18,3,8,1};
    heap1.buildMaxHeap(A,15);
    heap1.printTree();
    cout << "___________________________________________________________________________________________________________________\n\n";
    heap.heapSort(A,15);
    heap.print();

    cout << endl;
    system("pause");
    return 0;
}