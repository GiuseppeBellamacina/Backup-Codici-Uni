 /*
 Esercizio su ricorsione:
 Sommare gli elementi di una lista
 */
#include <iostream>
using namespace std;
#define N 5

/*
somma(v,i) = v[0]		se  i=0
v[i] + somma(v,i-1)		altrimenti

*/
int listSum(int v[], int i=N-1){
    string multiTab = string(N-i,'\t');
    cout << endl << multiTab;

    cout << "v["<<i<<"]:\t" << v[i] << "\t";
    if(i==0){
        cout << "==> return " << v[0];
        return v[0];
    }
    cout << "==> return" << v[i]
        << " + listSum(v,"<<(i-1)<<")";
    return v[i] + listSum(v, i-1);
}

 int main(){

    int vec[N]={10,20,30,40,50};
    int res = listSum(vec);

    cout << endl << "Somma=\t" << res << endl;
    return 0;
 }
