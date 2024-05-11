#include <iostream>
#include <iomanip>

#include <cstdlib>

using namespace std; 

/* 

Modificare il programma nel seguente modo: 
- allocare una matrice quadrata di dimensioni min(n,m) x min(n,m)
- inizializzare la matrice con numeri double 
- calcolare e stampare la somma e la media degli elementi della 
diagonale principale 
- calcolare e stampare la somma e la media degli elementi della 
diagonale secondaria 
 
*/ 

int main(){

  cout << "Inserisci due numeri x>1, y>1" << endl;

  double x;
  double y; 

  unsigned int n; 
  unsigned int m; 

  if(!(cin >> x >> y)){
    cerr << "Errore di estrazione!" << endl;
    return -1;
  }

  else if(x<1 || y<1){
    cerr << "Input non valido! x=" << x  << ", y=" << y << endl; 
    return -1;
  }

  else{ // arrotondare x ed y agli interi piu vicini
    n = (int) (x+0.5); // conversione esplicita    
    m = (int) (y+0.5); // conversione esplicita    
    cout << "Input arrotondato, n=" << n << ", m=" << m << endl; 
  }

  //  2.2 --> 2.2 + 0.5 = 2.7; (int) --> 2
  //  2.7 --> 2.7 + 0.5 = 3.2; (int) --> 3

  // conversione esplicita, NECESSARIA!! 
  //  double r = ((double) rand())/RAND_MAX; // c-style 

  // n, m >1 
    
  double M[n][m]; // C++11 non lo consente, GNU gcc lo consente!
  double W[n][m]; 

  // visita per righe 
  for(unsigned int i=0; i<n; i++){ //
    //visita della riga i-esima di M
    for(unsigned int j=0; j<m; j++){ // a=10, b=20
      M[i][j] = (rand()/(RAND_MAX*1.0))*(20-10) + 10;
      cout << M[i][j] << " ";  
    }
    cout << endl;
  } 

    cout << endl;
    cout << endl;

  // visita per colonne
  for(unsigned int j=0; j<m; j++){ //
    //visita della colonna j-esima di W
    for(unsigned int i=0; i<n; i++){ // a=5, b=30
      M[i][j] = (rand()/(RAND_MAX*1.0))*(20-5) + 5;
      cout << M[i][j] << " ";  
    }
    cout << endl;
  } 
  
}
