/*
    Il programma funziona perfettamente
*/

#include <iostream>
#include <fstream>

using namespace std;

int lcsLength(string x, string y, int lx, int ly){
    // ricavo le lunghezze di x e y
    int m = lx;
    int n = ly;

    // alloco c
    int **c = new int*[m+1];
    for (int i=0; i<=m; i++){
        c[i] = new int[n+1];
    }

    // inizializzo c
    for (int i=1; i<=m; i++){
        c[i][0] = 0; // opero sul primo indice con m
    }
    for (int j=0; j<=n; j++){
        c[0][j] = 0; // opero sul secondo indice con n
    }

    // avvio l'algoritmo
    for (int i=1; i<=m; i++){ // i va da 1 a m
        for (int j=1; j<=n; j++){ // j va da 1 a n
            if (x[i-1] == y[j-1]){ // ricordarsi che le stringhe partono da 0
                c[i][j] = c[i-1][j-1] + 1;
            } else if (c[i-1][j] >= c[i][j-1]){
                c[i][j] = c[i-1][j];
            } else {
                c[i][j] = c[i][j-1];
            }
        }
    }

    int ret = c[m][n];

    for (int i=0; i<=m; i++){
        delete[] c[i];
    }
    delete[] c;

    return ret;
}

void read(fstream &in, int &lx, int &ly, string &x, string &y){
    in >> lx;
    in >> ly;
    in >> x;
    in >> y;
}

int main(){
    string x, y;
    int m, n;
    fstream in, out;
    in.open("input.txt", fstream::in);
    out.open("output.txt", fstream::out);

    for (int i=0; i<100; i++){
        read(in, m, n, x, y);

        int c = lcsLength(x, y, m, n);

        out << c << endl;
    }

    in.close();
    out.close();

    return 0;
}