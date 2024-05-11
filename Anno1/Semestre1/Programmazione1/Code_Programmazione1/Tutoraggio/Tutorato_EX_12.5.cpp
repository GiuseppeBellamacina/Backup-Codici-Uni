#include <iostream>
#include <sstream>

using namespace std; 

int main(){

  string s[5]; 
  double x[5];  

  short is=0;  // indice per il vettore s
  short ix=0; // indice per il vettore x

  string input;

  cout << "Inserisci 5 argomenti (3 stringhe e 2 numeri): " << endl;
  // 1 fase, raccogliere l'input 
  getline(cin, input); //legge fino al carattere '\n' 
//  cin >> input; // legge i caratteri fino al carattere ' '

  stringstream ss;
  ss << input; 
  cout << "input: " << ss.str() << endl; 

  // TODO Completare con il controllo EOF
  // 2 fase, processare l'input dallo stringstream
  for(short c=0; c<5; c++){ // 5 tentativi di lettura 
    ss >> x[ix]; // lettura di un numero
    if(ss.fail()){ // errore di estrazione, non vi e' il numero
      ss.clear();
      ss >> s[is]; // estrazione di una stringa
      if(ss.fail())
	cerr << "Errore!!" << endl; 
      else
	is++; 
    }

    else
      ix++;
  }

  //is==3 && ix ==2   

  //c=5 
  // is, ix? 
  // ix=2 --> 2 elementi in x[]
  // is=3 --> 3 elementi in s[]

//  if(!(is==3 && ix==2))
    if(is!=3 || ix!=2)
      cout << "Input non valido!" << endl; 

  //stampa elementi array x
  cout << "Array x: " << endl; 
  for(short i=0; i<ix; i++)
    cout << x[i] << endl; 

  //stampa elementi array s
  cout << "Array s: " << endl; 
  for(short i=0; i<is; i++)
    cout << s[i] << endl; 
}
