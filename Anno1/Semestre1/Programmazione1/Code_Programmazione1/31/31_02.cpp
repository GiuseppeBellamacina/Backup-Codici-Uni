#include <iostream>

using namespace std;

template <typename T>
//consente solo le chiamate Scambia(t1, t2)
//con typeid(t1) == typeid(t2) 
void Scambia (T & a, T & b) // passaggio by reference
  {
    static int i = 0; 
    i++; 
    //Indirizzo campo static permettera' di capire 
    //che le specializzazioni differiscono 
    // in base alle differenti chiamate 
    cout << "Scambia(T, T), " << &i << ", i=" << i << endl; 

    T aux;

    aux = a;
    a = b;
    b = aux;
}


//Stessa funzione template, 
//stesso nome ma DUE TIPI GENERICI 
template <typename T, class C>
//permette (anche) le chiamate Scambia (t1, t2) con typeid(t1)!=typeid(t2)
void Scambia (T & a, C & b) // passaggio by reference
  {
    static int i = 0; 
    i++; 
    cout << "Scambia(T, C), " << &i << ", i=" << i << endl; 

    T aux;

    aux = a;
    a = (T) b; // cast esplicito o implicito con eventuali operatori di conversione..
    b = (C) aux; 
  }


int main ()
  {
    int   i = 6,    j = 9;    int k=8; 
    float x = 1.6,  y = 3.3;  float z = 9.8; 
    
    cout << "Prima : " << i << "  " << j << "\n";
    Scambia (i, j); // Scambia(int, int);
    cout << "Dopo  : " << i << "  " << j << "\n\n";

    cout << "Prima : " << i << "  " << k << "\n";
    Scambia (i, k); // Scambia(int, int);
    cout << "Dopo  : " << i << "  " << k << "\n\n";

    cout << "Prima : " << x << "  " << y << "\n";
    Scambia (x, y); // Scambia(float, float);
    cout << "Dopo  : " << x << "  " << y << "\n\n";

    cout << "Prima : " << x << "  " << z << "\n";
    Scambia (x, z); // Scambia(float, float);
    cout << "Dopo  : " << x << "  " << z << "\n\n";

    /* Adesso questa chiamata non produrra' alcun errore di 
    * compilazione 
    */ 
    cout << "Prima : " << i << "  " << x << "\n";
    Scambia (i, x);   // Scambia(int, float);
    cout << "Dopo  : " << i << "  " << x << "\n\n";

    return 0;
  }
