/*
    Il programma funziona perfettamente
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int edit(string x, string y, int lx, int ly){
    int m = lx;
    int n = ly;

    int **M = new int*[m+1];
    for(int i=0; i<=m; i++)
        M[i] = new int[n+1];

    for (int i=0; i<=m; i++)
        M[i][0] = i;
    for (int j=0; j<=n; j++)
        M[0][j] = j; // se metto M[0][j] = 0 ottengo la ricerca di occorrenze approssimate

    for(int i=1; i<=m; i++){
        for(int j=1; j<=n; j++){
            int p;
            if (x[i-1] == y[j-1])
                p = 0;
            else
                p = 1;
            M[i][j] = min(M[i-1][j] + 1, min(M[i][j-1] + 1, M[i-1][j-1] + p));
        }
    }

    int result = M[m][n];

    for(int i=0; i<=m; i++)
        delete[] M[i];
    delete[] M;

    return result;
}

int main(){
    string x, y;
    int m, n;
    fstream in, out;
    in.open("input.txt", fstream::in);
    out.open("output.txt", fstream::out);

    for(int i=0; i<100; i++){
        in >> m;
        in >> n;
        in >> x;
        in >> y;
        out << edit(x, y, m, n) << endl;
    }

    in.close();
    out.close();
    return 0;
}