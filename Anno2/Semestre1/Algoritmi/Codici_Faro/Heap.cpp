#include <iostream>
#include <ctime>
#include <math.h>
using namespace std;

template <class T> class PriorityQueue {
	public:
		virtual T* extractMax() = 0;
		virtual PriorityQueue<T>* enqueue(T x) = 0;
		virtual int size() = 0;
};

template <class H> class BinaryHeap : public PriorityQueue<H>{
	private:
		H **A;
		int heapsize;
		int len;
		int left(int i) { return i<<1; }
		int right(int i) { return (i<<1)|1; }
		int parent(int i) { return i>>1; }
		
		void scambia(int i, int j) {
			H* tmp = A[i];
			A[i] = A[j];
			A[j] = tmp;
		}
		
		void heapify(int i) {
			if(i>heapsize) return;
			int l = left(i);
			int r = right(i);
			int max = i;
			if(l<=heapsize && compare(A[max], A[l])<0) max=l;
			if(r<=heapsize && compare(A[max], A[r])<0) max=r;
			if(max==i) return;
			scambia(i,max);
			heapify(max);
		}
		
		
	public:
		virtual int compare(H *a, H *b)=0;
		BinaryHeap(int size) {
			A = new H*[size];
			len = size;
			heapsize = 0;
		}
		
		H* extractMax() {
			if(heapsize==0) return NULL;
			scambia(1, heapsize);
			heapsize--;
			heapify(1);
			return A[heapsize+1];
		}
		
		BinaryHeap<H>* enqueue(H x) {
			heapsize += 1;
			A[heapsize] = new H(x);
			int i = heapsize;
			while(i>1 && compare(A[i],A[parent(i)])>0) {
				scambia(i, parent(i));
				i = parent(i);
			}
			return this;
		}
		
		BinaryHeap<H>* increaseKey(int i, H *k) {
			if(i>heapsize) return this;
			if(i<1) return this;
			if( *A[i] >= *k ) return this;
			*A[i] = *k;
			while(i>1 && compare(A[i],A[parent(i)])>0) {
				scambia(i, parent(i));
				i = parent(i);
			}
			return this;
		}
		
		int size() {
			return heapsize;
		}
		
		void print() {
			cout << "HEAP : ";
			for(int i=1; i<=heapsize; i++) 
				cout << *A[i] << " ";
			cout << endl;
		}
};

template <class H> class MaxBinaryHeap : public BinaryHeap<H> {
	private: 
	public:
		int compare(H* a, H *b) {
			return (*a)-(*b);
		}
		MaxBinaryHeap(int size) : BinaryHeap<H>(size) {}
};

template <class H> class MinBinaryHeap : public BinaryHeap<H> {
	private: 
	public:
		int compare(H* a, H *b) {
			return (*b)-(*a);
		}
		MinBinaryHeap(int size) : BinaryHeap<H>(size) {}
};

int main() {
	MinBinaryHeap<int> *B = new MinBinaryHeap<int>(100);
	B->enqueue(2)->enqueue(5)->enqueue(23);
	B->print();
	return 1;
}
