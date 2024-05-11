#include <iostream>

//no name clash! 
//nomi uguali protetti da 
//namespace! 
#include "alpha.h"
#include "beta.h"

using namespace std; 

 using namespace alpha; // (1) importa qualunque nome definito nel namespace alpha 
 using namespace beta; // (2) importa qualunque nome definito nel namespace beta

/* 
* Istruzioni (1) e (2) ammesse, ma ClasseX per alpha o per beta dovra' 
* specificare lo scope (il namespace), altrimenti si avra'; ambiguita'
*/

int main(){

  // (3) Del namespace beta, solo ClasseX !  
  //using beta::ClasseX; 
  //using alpha::ClasseX; 

  //Necessariamente per una delle variabili istanza andra' 
  //specificato il namespace 

  ClasseX xbeta("abcd");  // namespace beta..
  ClasseX xalpha(10); // namespace alpha..
//  ClasseX xlapha(10); // (4) 

  cout << xalpha.getAlpha() << endl;
  cout << xbeta.getBeta() << endl; 

}
