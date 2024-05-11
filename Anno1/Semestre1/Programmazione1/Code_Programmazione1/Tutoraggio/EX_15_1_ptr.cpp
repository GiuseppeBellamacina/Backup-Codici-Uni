#include <iostream>
#include <iomanip>

#include <cstdlib>

using namespace std; 

int main(){

  cout << "Inserisci un numero p>1" << endl;

  double x;
  unsigned int n; 

  if(!(cin >> x)){
    cerr << "Errore di estrazione!" << endl;
    return -1;
  }

  else if(x<1){
    cerr << "Input non valido! x=" << x  << endl; 
    return -1;
  }

  else{ // arrotondare x all'intero piu vicino
    n = (int) (x+0.5); // conversione esplicita    
    //n = (x+0.5); // conversione implicita
    cout << "Input arrotondato: " << n << endl; 
  }

  //  2.2 --> 2.2 + 0.5 = 2.7; (int) --> 2 
  //  2.7 --> 2.7 + 0.5 = 3.2; (int) --> 3

  // conversione esplicita, NECESSARIA!! 
  //  double r = ((double) rand())/RAND_MAX; // c-style 

  // allocazione automatica
  // int V[n]; // C++11-->NO!, ma GNU gcc lo permette
  // int W[n]; // C++11-->NO!, ma GNU gcc lo permette
  // int Z[n]; // C++11-->NO!, ma GNU gcc lo permette

  // allocazione dinamica 
  int *V = new int[n]; // allocazione dinamica
  int *W = new int[n]; // allocazione dinamica
  int *Z = new int[n]; // allocazione dinamica
  // int V[n]; int V[10]; 
  
  //inizializzare V

    // *(V+1) = ... // V[1] = ... 
    // V[0] --> prima cella --> *(V+0)
    // *(V+1) --> seconda cella --> V[1]
    // 
    // *(V+n-1) --> ultima cella --> V[n-1]
      // *(V+k) = 10 

    // (V+k) == &V[k]
    // *(V+k) == V[k]
  for(unsigned int i=0; i<n; i++)
    *(V+i) = rand()%21;  // *(V+0) = ... // V[0] = .. 

  //inizializzare W
  unsigned int j=0;
  while(j++<n)
    W[j] = rand()%11;  

  //inizializzare Z
  j=0; 
  do{ // numeri nell'intervallo [5,15]
    // rand()%(b-a+1) + a
    Z[j] = rand()%(15-5+1) + 5; 
    j++;
  }while(j<n);

  // Per esercizio, modificare usando la 
  // funzione setw()
  // header <iomanip> 
  cout << "V  " << "W  " << "Z	" << endl; 
  cout << "-------------" << endl; 
  for(unsigned int c=0; c<n; c++){
    cout << V[c] << "  " << W[c] << "  " << Z[c] << endl; 
  }

  // stampiamo gli indirizzi degli elementi 
  // del vettore V

  cout << "ARRAY V, equivalenza espressioni" << endl; 

  cout << "(V+c)" << "  &V[c]" << endl; 
  for(unsigned int c=0; c<n; c++){
    cout << (V+c) << " " << &V[c] << endl; 
  }

  cout << "*(V+c)" << "  V[c]" << endl; 
  for(unsigned int c=0; c<n; c++){
    cout << *(V+c) << " " << V[c] << endl; 
  }

  
}
