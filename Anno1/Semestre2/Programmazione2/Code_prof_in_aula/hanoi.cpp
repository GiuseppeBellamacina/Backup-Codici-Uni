
/*


*/
#include <iostream>
using namespace std;
/*
iniziale: piolo da cui prendere il piatto (sorgente)
centrale: piolo di supporto (appoggio)
finale: piolo di destinazione del piatto (destinazione)
n: piatto da posizionare
*/
void hanoi(char iniziale, char centrale, char finale, int n){

    if(n==1)
        cout << "Muovo il disco 1 dal piolo " << iniziale
             << " al piolo " << finale << endl;
    else{
        //Spostare n-1 dischi dal piolo iniziale al centrale
        hanoi(iniziale, finale, centrale,n-1);
        cout << "Muovo il disco " << n
             << " dal piolo " << iniziale
             << " al piolo " << finale << endl;
        //Spostare n-1 dischi dal centrale al finale...
        //... usando il piatto inizale come ausiliario
        hanoi(centrale, iniziale, finale, n-1);
    }

}

int main(){

    int numDischi;
    cout << "Inserire un intero positivo: ";
    cin >> numDischi;
    if(numDischi<=0) cout << "Numero non positivo" << endl;
    else{

        cout << "Con " << numDischi << " dischi,"
             << " la sequenza di mosse e':" << endl;
        hanoi('A', 'B', 'C', numDischi);
    }
    return 0;
}
