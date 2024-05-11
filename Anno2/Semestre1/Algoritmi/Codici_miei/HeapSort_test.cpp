// ATTENZIONE: questo programma e' stato fatto ad minchiam per testare certe cose.
// In gran parte non funziona, quindi vedi "Class_MaxHeap.cpp" o l'altro simile

#include <iostream>
#include <cmath>

using namespace std;

template <typename T>
void swap(T* arr, T i, T j){
    T tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

template <typename T>
int left(T* arr, int i){
    return 2*(i+1)-1;
}

template <typename T>
int right(T* arr, int i){
    return 2*(i+1);
}

template <typename T>
void heapify(T* arr, int len, int i){
    int max = i;
    int l = left(arr, i);
    if(l<len && arr[l]>arr[max])  max = l;
    int r = right(arr, i);
    if(l<len && arr[r]>arr[max])  max = r;
    if(max != i){
        swap(arr, max, i);
        heapify(arr, len, max);
    }
}

template <typename T>
void buildMaxHeap(T* arr, int len){
    for(int i=(len/2)-1; i>=0; i--) heapify(arr, len, i);
}

// da sistemare
template <typename T>
T extractMax(T* arr, int& len){
    swap(arr, 0, len-1);
    len = len-1;
    heapify(arr, len, 0);
    cout << len;
    return arr[len];
}

template <typename T>
void heapSort(T* arr, int n){
    int heapsize = n;
    buildMaxHeap(arr, n);
    for(int i=0; i<heapsize; i++) extractMax(arr, n);
}

template <typename T>
void print(T* arr, int len){
    for(int i=0; i<len; i++) cout << arr[i] << '\t';
    cout << endl;
}


int main(){
    int n=3;
    int A[n];
    for(int i=0; i<n; i++) A[i] = i+1;
    cout << "Array normale:\n";
    print(A,n);
    cout << "MaxHeap:\n";
    buildMaxHeap(A,n);
    print(A,n);
    cout << "Max: " << extractMax(A,n) << endl;
    cout << "MaxHeap dopo estrazione:\n";
    print(A,n);

    return 0;
}
