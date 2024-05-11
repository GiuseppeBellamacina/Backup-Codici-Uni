/*
    Il programma funziona perfettamente
*/

#include <iostream>
#include <fstream>

using namespace std;

int*** lcsLength(string x, string y, int lx, int ly){
    // ricavo le lunghezze di x e y
    int m = lx;
    int n = ly;
    
    /* devo allocare c con i valori delle lunghezze
       mentre b con le direzioni
       b e c hanno le stesse dimensioni (m+1)x(n+1)*/

    // alloco c
    int **c = new int*[m+1];
    for (int i=0; i<=m; i++){
        c[i] = new int[n+1];
    }

    // alloco b
    int **b = new int*[m+1];
    for (int i=0; i<=m; i++){
        b[i] = new int[n+1];
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
                b[i][j] = 7; // 7 significa che va in alto a sinistra
            } else if (c[i-1][j] >= c[i][j-1]){
                c[i][j] = c[i-1][j];
                b[i][j] = 8; // 8 significa che va in alto
            } else {
                c[i][j] = c[i][j-1];
                b[i][j] = 4; // 4 significa che va a sinistra
            }
        }
    }

    // alloco ret
    int ***ret = new int**[2];
    ret[0] = c;
    ret[1] = b;

    return ret;
}

void printLcs(int **b, string x, int i, int j, fstream &out){
    if (i == 0 || j == 0){
        return;
    }
    if (b[i][j] == 7){
        printLcs(b, x, i-1, j-1, out);
        out << x[i-1];
    } else if (b[i][j] == 8){
        printLcs(b, x, i-1, j, out);
    } else {
        printLcs(b, x, i, j-1, out);
    }
}

void dealloc(int ***cb, int m, int n){
    int **c = cb[0];
    int **b = cb[1];

    for (int i=0; i<=m; i++){
        delete[] c[i];
    }
    delete[] c;

    for (int i=0; i<=m; i++){
        delete[] b[i];
    }
    delete[] b;

    delete[] cb;
}

void read(fstream &in, int &lx, int &ly, string &x, string &y){
    in >> ly;
    in >> lx;
    in >> y;
    in >> x;
    // sono invertiti per risolvere
    // la cosa degli indici di y
}

int main(){
    string x, y;
    int m, n;
    fstream in, out;
    in.open("input.txt", fstream::in);
    out.open("output.txt", fstream::out);

    for (int i=0; i<100; i++){
        read(in, m, n, x, y);

        int ***cb = lcsLength(x, y, m, n);
        int **b = cb[1];

        printLcs(b, x, m, n, out);
        out << endl;

        dealloc(cb, m, n);
    }

    in.close();
    out.close();

    return 0;
}