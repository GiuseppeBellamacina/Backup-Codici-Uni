#include <iostream>
#include <iomanip>

using namespace std; 

int main(){

  unsigned int somma = 0; 

  // 1
  for(unsigned int i=1; i<=99; i++){
    if(i%2!=0 && i%3!=0)
      somma+=i; 
  }

  cout << "Sol.1. Somma=" << somma << endl;   

  // 2
  somma=0;       
  for(unsigned int i=1; i<=99; i+=2){
    if(i%3!=0) // if(i%3)
      somma+=i; 
  }

  cout << "Sol.2. Somma=" << somma << endl;   

  // 3 ?? NO.  Perche? 
  somma=0;       
  for(unsigned int i=1; i<=99 && i%3!=0 && i%2!=0; i++){
    somma+=i; 
  }

  cout << "NON Sol. 3. Somma=" << somma << endl;   

  // 4
  somma=0;       
  for(unsigned int i=1; i<=99; i+=6){
      somma+=i; 
  }

  for(unsigned int i=5; i<=99; i+=6){
      somma+=i; 
  }

  cout << "Sol.4 Somma=" << somma << endl;   

}
