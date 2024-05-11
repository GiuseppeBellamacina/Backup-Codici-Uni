#include <iostream>
#include <iomanip>

#include <limits>

using namespace std; 

int main(){

  float x = -1; 

  cout << "1.Inserisci un numero: " << endl; 

  cin >> x; // tentativo di estrazione da stdin (tastiera)
  if(cin.fail()){ // true se e' avvenuto un errore di IO 
    cout <<"1.Il numero inserito non e' valido! " << endl; 
    cin.clear(); 

    cin.ignore();      
    
    cout << "2.Inserisci un altro numero: " << endl; 
    cin >> x;
    if(cin.fail())
      cout << "2.Ulteriore errore!"; 
    else
      cout << "x = " << x << endl; 
  }
  else
    cout << "x = " << x << endl; 
}
