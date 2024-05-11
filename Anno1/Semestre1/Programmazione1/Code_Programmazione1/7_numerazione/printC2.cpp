#include <iostream>

#include "printBits.h"

using namespace std;

/* 
* Mostra le due componenti 
* della rappresentazione in complemento a due 
* se l'argomento e' negativo.. 
*/ 
void scomponiCompl2(short int b){

  if(b>=0){ //non e' di segno negativo 
    cout << "Il numero " << b <<  " e' positivo!"  << endl; 
    return; 
  }

  //Questa e' una ``word'' di 16 bit: 100...0 
  unsigned short int x = (1 << (sizeof(unsigned short int)*8-1));
  	
  // y  rappresenta la stringa di 15 bit a "destra" del MSB (=1)
  cout << "Nella rappresentazione COMPL a 2 del numero " << b << " deve essere 2^" << (sizeof(unsigned short)*8-1) << " - y = " << -b << ", dove 2^" << (sizeof(unsigned short )*8-1)  << " = " <<  x << "\n\n"; 

  //sottraggo al numero x = (2^15) il numero +99 per ottenere 
  // il numero (positivo) rappresentato
  // dai 15 bit (da 0 a 14) della rappresentazione in complemento 
  // a 2 del numero b
  short y = x - (-b);
  cout << "Quindi y = " << y << " = ";
  printBits<short>((short*)&y, sizeof(y)*8); 
  cout << "\n\n" ;

  //infatti..
  // ~ e' NOT bitwise, & e' AND bitwise
  unsigned short z = (~x & (unsigned short) b);

  //ecco il numero (positivo) corrispondente ai bit 0...14 della 
  //rappresentazione complemento a 2 del numero b
  cout << "Adesso estraiamo i bit 14...0 della rappr. in complemento a 2 del numero b=" << b; 
  
  cout << "\n Dunque z= "; 

  printBits<unsigned short>(&z, sizeof(unsigned short)*8);

  cout << (z == y ? " = y. OK!" : " != y. ??") << endl; 

  cout << "\n";

}

int main(){

  // Numero intero positivo 
  short int a = 113;

  // Numero intero negativo 
  short int b = -99;

  //Print a in binary form 
  cout << "a = " << a << " = ";
  
  printBits<short int>(&a, sizeof(short)*8); 

  cout << "\n\n"; 

  // Print b in binary form 
  cout << "b = " << b << " = ";

  printBits<short int>(&b, sizeof(b)*8);

  cout << "\n\n";

  scomponiCompl2(b);
  
}
