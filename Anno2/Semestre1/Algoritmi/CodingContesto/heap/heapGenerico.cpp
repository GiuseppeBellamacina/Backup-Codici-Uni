/*
    Questo contiene le implementazioni
    generiche di heap e heapsort
    in pìu ho aggiunto la funzione to_print
    che trasforma l'array in una stringa da poter stampare
    per il resto è necessario modificare il codice
*/

#include <iostream>
#include <cstdlib>

using namespace std;

template <typename T>
class Heap{
    public:
        T* arr;
        int maxSize;
        int heapSize;
        virtual void heapify(int i) = 0;
        int left(int i){return 2*i + 1;}
        int right(int i){return 2*i + 2;}
        int parent(int i){
            if(i%2 == 0) return i/2 - 1;
            else return i/2;
        }
        Heap(int size){
            maxSize = size;
            heapSize = 0;
            arr = new T[maxSize];
        }
        virtual void insert(T key) = 0;
        string to_print(){
            string str = "";
            for(int i=0; i<heapSize; i++){
                str += to_string(arr[i]) + " "; // non funziona con i cha e i bool
            }
            return str;
        };
};

template <typename T>
class MaxHeap : public Heap<T>{
    public:
        void heapify(int i){
            int max = i;
            int l = this->left(i);
            int r = this->right(i);
            if(l < this->heapSize && this->arr[l] > this->arr[max]) max = l;
            if(r < this->heapSize && this->arr[r] > this->arr[max]) max = r;
            if(max != i){
                swap(this->arr[i], this->arr[max]);
                heapify(max);
            }
        }
        MaxHeap(int size) : Heap<T>(size){}
        void insert(T key){
            if(this->heapSize == this->maxSize){
                cout << "Heap overflow" << endl;
                return;
            }
            this->heapSize++;
            this->arr[this->heapSize-1] = key;
            int i = this->heapSize-1;
            while(i>0 && this->arr[this->parent(i)] < this->arr[i]){
                swap(this->arr[this->parent(i)], this->arr[i]);
                i = this->parent(i);
            }
        }
        T extractMax(){
            if(this->heapSize == 0){
                cout << "Heap underflow" << endl;
                exit(1);
            }
            swap(this->arr[0], this->arr[this->heapSize-1]);
            this->heapSize--;
            heapify(0);
            return this->arr[this->heapSize];
        }
        void increaseKey(int i, T key){
            if(key < this->arr[i]){
                cout << "New key is smaller than current key" << endl;
                return;
            }
            this->arr[i] = key;
            while(i>0 && this->arr[this->parent(i)] < this->arr[i]){
                swap(this->arr[this->parent(i)], this->arr[i]);
                i = this->parent(i);
            }
        }
};

template <typename T>
MaxHeap<T> buildMaxHeap(T *arr, int size){
    MaxHeap<T> heap(size);
    heap.arr = arr;
    heap.heapSize = size;
    for(int i=size/2-1; i>=0; i--){
        heap.heapify(i);
    }
    return heap;
}

template <typename T>
T* maxHeapSort(T *arr, int size){
    MaxHeap<T> heap = buildMaxHeap(arr, size);
    T *sorted = new T[size];
    for(int i=0; i<size; i++){
        sorted[i] = heap.extractMax();
    }
    return sorted;
}

template <typename T>
class MinHeap : public Heap<T>{
    public:
        void heapify(int i){
            int min = i;
            int l = this->left(i);
            int r = this->right(i);
            if(l < this->heapSize && this->arr[l] < this->arr[min]) min = l;
            if(r < this->heapSize && this->arr[r] < this->arr[min]) min = r;
            if(min != i){
                swap(this->arr[i], this->arr[min]);
                heapify(min);
            }
        }
        MinHeap(int size) : Heap<T>(size){}
        void insert(T key){
            if(this->heapSize == this->maxSize){
                cout << "Heap overflow" << endl;
                return;
            }
            this->heapSize++;
            this->arr[this->heapSize-1] = key;
            int i = this->heapSize-1;
            while(i>0 && this->arr[this->parent(i)] > this->arr[i]){
                swap(this->arr[this->parent(i)], this->arr[i]);
                i = this->parent(i);
            }
        }
        T extractMin(){
            if(this->heapSize == 0){
                cout << "Heap underflow" << endl;
                exit(1);
            }
            swap(this->arr[0], this->arr[this->heapSize-1]);
            this->heapSize--;
            heapify(0);
            return this->arr[this->heapSize];
        }
        void decreaseKey(int i, T key){
            if(key > this->arr[i]){
                cout << "New key is bigger than current key" << endl;
                return;
            }
            this->arr[i] = key;
            while(i>0 && this->arr[this->parent(i)] > this->arr[i]){
                swap(this->arr[this->parent(i)], this->arr[i]);
                i = this->parent(i);
            }
        }
};

template <typename T>
MinHeap<T> buildMinHeap(T *arr, int size){
    MinHeap<T> heap(size);
    heap.arr = arr;
    heap.heapSize = size;
    for(int i=size/2-1; i>=0; i--){
        heap.heapify(i);
    }
    return heap;
}

template <typename T>
T* minHeapSort(T *arr, int size){
    MinHeap<T> heap = buildMinHeap(arr, size);
    T *sorted = new T[size];
    for(int i=0; i<size; i++){
        sorted[i] = heap.extractMin();
    }
    return sorted;
}