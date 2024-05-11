#include <iostream>
#include <iomanip>

using namespace std; 

int main(){

  float x = -1; 

  cout << "Inserisci un numero: " << endl; 

  //1
  /*  
  if(cin >> x) // 
    cout << "x = " << x << endl; 
  else
    cout <<"Il numero inserito non e' valido! " << endl; 

  cout << "Inserisci un numero: " << endl; 
  */

  /*
  //2
  if(!(cin >> x)) // 
    cout <<"Il numero inserito non e' valido! " << endl; 
  else
    cout << "x = " << x << endl; 
  */ 

  cin >> x; 
  if(cin.fail()) // true se e' avvenuto un errore di IO 
    cout <<"Il numero inserito non e' valido! " << endl; 
  else
    cout << "x = " << x << endl; 
}
