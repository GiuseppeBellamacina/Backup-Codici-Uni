
/*
Esercizio 2:
Definire più metodi per stampare i numeri primi minori o uguali ad n,
e valutare il loro tempo di esecuzione per valori di n crescenti.
*/
#include <iostream>
#include <cmath>

using namespace std;
bool print;


/* Metodo 1:
per ogni numero num da 2 a n:
    cerco un divisore di num dentro [2, num/2]
    se non lo trovo, num e' primo.
Esempio:
    num = 8

    8/2   8/3  8/4 ....   8/8
    4   >  ?  > 2  ... >   1
*/
void metodoNmezzi(int n){
    int num =2;
    int div, lim;
    bool primo;
    while(num<=n){
        //cerco un div che divide num in [2, num/2]
        div =2;
        primo=true;
        lim = floor(num/2);
        while(div<=lim){
            if(num%div == 0){
                primo = false;
                break;
            }
            div++;
        }
        if(primo&& print)
            cout << num << "\t";
        num++;
    }
}

/*  Metodo2:
    sia num intero in [1,n]
    num = sqrt(num)*sqrt(num)
    num =a*b     num, a, b interi > 1
    se uno tra a e b e' >sqrt(num) allora l'altro deve essere <sqrt(num)
    quindi cerchiamo l'altro, che si trovera' in [2, sqrt(num)]
*/
void metodoSqrt(int n){

    int num = 2, div;
    bool primo;
    int lim;
    while(num <=n){
        div = 2;
        primo = true;
        lim = (int)sqrt(num);
        while(div<=lim){
            if(num%div == 0){
                primo = false;
                break;
            }
            div++;
        }

        if(primo&& print)
            cout << num << "\t";
        num++;
    }
}

/*
    Metodo 3: Crivello di Eratostene
    elenco tutti i numeri da 2 a n
    elimino i multipli di 2
    elimino i multipli di 3
    ...
    appena trovo il primo numero che non ha multipli mi fermo
*/

void eratostene(int n){
    int i;
// vec mi dice se un numero e' primo oppure no
    bool vec[n];
    for(i=2;i<n;i++) vec[i] = true;
    for(i=2;i<n;i++)
        if(vec[i])
            for(int j=i; j*i <n; j++)
                /*
                 i = 2      i*j = 2*2  2*3 ...
                 i = 3      i*j = 3*3  2*4 ...
                */
                vec[i*j] = false;

    for(i=2;i<n;i++)
        if(vec[i] && print)
            cout << i << "\t";
}
int main(){
    int n;
    print = true;
    cout << "Inserisci n: ";
    cin >> n;
    if(n>100) print = false;

    cout << "Ricerca in [2, num/2] per num in [2, "<<n<<"]" << endl;
    cout << "Numeri primi fino ad "<< n <<":"<< endl;
    metodoNmezzi(n);

    cout << endl << "Ricerca in [2, sqrt(num)] per num in [2, "<<n<<"]:"<< endl;
    cout << "Numeri primi fino ad "<< n <<":"<< endl;
    metodoSqrt(n);

    cout << endl << "Crivello di Eratostene:" << endl;
    cout << "Numeri primi fino ad "<< n <<":"<< endl;
    eratostene(n);
    return 0;
}
