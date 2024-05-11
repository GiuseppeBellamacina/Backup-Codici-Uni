#include <iostream>
#define N 10

using namespace std;

template <typename T>
T findMin(T* arr, int n){
    T min = arr[0];
    for(int i=1; i<n; i++){
        if(arr[i] < min) min = arr[i];
    }
    return min;
}

template <typename T>
T findMax(T* arr, int n){
    T max = arr[0];
    for(int i=1; i<n; i++){
        if(arr[i] > max) max = arr[i];
    }
    return max;
}

template <typename T>
void arrCopy(T* arr1, T* arr2, int n){
    for(int i=0; i<n; i++) arr2[i] = arr1[i];
}

template <typename T>
T* countingSort(T* A, int n){ // countingSort non stabile
    T max = findMax(A,n);     // gestisce i negativi già da se'
    T min = findMin(A,n);     // per i double implementare doubleCheck
    int range = max-min+1;
    T* C = new T[range];      // C conterrà il numero di occorrenze degli elementi

    for(int i=0; i<range; i++) C[i] = 0;
    for(int i=0; i<n; i++) C[A[i]-min]++;

    T* B = new T[n];
    int z=0;
    for(int i=0; i<range; i++){
        for(int j=0; j<C[i]; j++)
            B[z++] = i+min;
    }
    
    return B;
}

template <typename T>
void countingSortStabile(T* A, int n){
    T max = findMax(A,n);
    T min = findMin(A,n);
    int range = max-min+1;
    T* C = new T[range];

    for(int i=0; i<range; i++) C[i] = 0;
    for(int i=0; i<n; i++) C[A[i]-min]++; // C contiene il numero di elementi uguali a i-min

    T* B = new T[n];
    for(int i=1; i<range; i++)
        C[i] = C[i] + C[i-1]; // C contiene il numero di elementi <= a i-min
    for(int i=n-1; i>=0; i--){
        B[C[A[i]-min]-1] = A[i];
        C[A[i]-min]--;
    }

    arrCopy(B,A,n);
    delete[] B;
    delete[] C;
}

/*void radixSort(string* A, int n, int d){
    string** B = new string*[d];
    for(int i=0; i<d; i++)
        B[i] = new string[n];
    
    for(int i=0; i<d; i++){
        for(int j=0; j<n; j++){
            B[i][j] = A[i][j];
        }
    }

    for(int i=d-1; i>=0; i--)
        countingSortStabile(B[i], n);
}*/

int main(){
    int A[N] = {2,3,3,6,3,5,4,2,5,3};
    countingSortStabile(A,N);
    for(int i=0; i<N; i++) cout << A[i] << '\t';

    cout << endl;

    //string str[N] = {"333", "332", "331", "323", "313", "133", "233", "222", "221", "111"};
    //radixSort(str, N, 3);
    //for(int i=0; i<N; i++) cout << str[i] << '\t';

    return 0;
}
