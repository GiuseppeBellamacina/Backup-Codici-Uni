/*
    Il programma funziona perfettamente
*/

#include <iostream>
#include <fstream>
#include <climits>
#include <string>
#include <cstdlib>
using namespace std;

int MatrixChain(int* vett, int n){
    int **m = new int *[n]; // n sono le dimensioni
    for(int i=0; i<n; i++) // la funzione parte con n posto con 1 in più
        m[i] = new int[n];

    for(int i = 1; i < n; i++) // i va da 1 a n-1
        m[i][i] = 0;
    
    for(int l = 2; l < n; l++){ // l è la lunghezza della catena e va da 2 a n-1
        for(int i = 1; i < n-l+1;i++){ // i va da 1 n-l
            int j = i+l-1; // a j si mette i+l-1

            m[i][j] = INT_MAX;

            for(int k = i; k <= j-1; k++){ // k va da i a j-1
                int q = m[i][k] + m[k+1][j] + vett[i-1]*vett[k]*vett[j]; // attento a k+1 e i-1

                if(q < m[i][j])
                    m[i][j] = q;
            }
        }
    }
    
    int ret =  m[1][n-1]; // ritorna il valore per n matrici (n era inizializzato con 1 in più)
    for(int i = 0; i < n; i++)
        delete[] m[i];
    delete[] m;
    return ret;
}


int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int i = 0; i < 100; i++){
        int n; in >> n;
        int* vett = new int[n+1];
        int r, c;

        for(int j = 0; j < n; j++){
            string line;
            getline(in, line);
            sscanf(line.c_str(), "(%dx%d)", &r, &c);
            vett[j] = r;
        }
        vett[n] = c;

        
        out << MatrixChain(vett, n+1) << endl;

        delete [] vett;
    }
}