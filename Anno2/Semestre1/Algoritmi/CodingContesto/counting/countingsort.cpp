// Fatto da Mattia e funziona
#include<iostream>
#include<fstream>

using namespace std;

void print(int* A, int size, ostream& out){
    for(int i=0; i<size; i++){
        out << A[i] << " ";
    }
}

int* CountingSort(int* A, int size, ostream& out){
    //troviamo il range dei valori dell'array
    int max=A[0];
    int min=A[0];
    for (int i=1; i<size; i++){
        if(A[i]>max) max = A[i];
        if(A[i]<min) min = A[i];
    }

    //calcolo del range ! importante il +1 !
    int k = max-min + 1;
    int *C = new int[k];
    for (int i=0; i<k; i++)
        C[i]=0;

    //contiamo le occorrenze di ogni elemento i, e inseriamo il conteggio in C[i]
    for (int i=0; i<size; i++)
        C[A[i]-min]++;

    //sommiamo a ogni C[i] il suo precedente -> 0 1 2 2 diventa 0 1 3 5 -> [0][0+1][1+2][3+2] 
    for (int i=1; i<k; i++)
        C[i] = C[i]+C[i-1];

    //spostiamo in avanti ogni elemento C[i] -> 0 1 3 5 diventa 0 0 1 3
    for (int i=k-1; i>0; i--)
        C[i] = C[i-1];
    C[0]=0;
    //otteniamo cosi' i posti dove dovremmo trovare la prima occorrenza di ogni i nell' array ordinato

    //stampiamo solo questo array per la prima meta' dell'esercizio 
    print(C, k, out);

    //nuovo array ordinato
    int* B = new int[size];

    //prendiamo una i per volta e scorriamo A, leggiamo su C il suo posto corretto e inseriamo i su B, poi aumentiamo il posto 
    //in modo che se leggiamo un numero uguale sarÃ  inserito subito dopo
    for (int i=0; i<size; i++){
        B[C[A[i]-min]] = A[i];
        C[A[i]-min]++;
    }
    return B;
}

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    int size;
    for(int i=0; i<100; i++){
        in >> size;
        int* Arr = new int[size];
        for (int j=0; j<size; j++){
            int key;
            in >> key;
            Arr[j] = key;
        }
        //non possiamo andare a modificare Arr per come funziona l'algoritmo, 
        //dobbiamo appoggiarci a un altro array e poi copiare
        Arr = CountingSort(Arr, size, out);
        print(Arr, size, out);
        out << endl;
        delete[] Arr;
    }
}