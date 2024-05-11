#include <string>
#include <iostream>
#include <typeinfo>

using namespace std; 

int main(){

  string str1 = "supercalifragilistichespiralidoso"; 

  //substr() -- restituisce una sottostringa
  string s1 = string(1,str1[0]);  // costruttore, vedi documentazione...
  
  //operatore binario + 
  string s2 = s1 + str1.substr(1,2); // operatore binario + su tipi string

  //le prime tre lettere di str1
  cout << "s2:" << s2 << endl; 

  //substr(): secondo argomento facoltativo 
  cout << "str1[10...]: " << str1.substr(10) << endl;  // ultimo carattere 

  //ma anche..
  cout << str1[0] << endl; 

  //cosa restituisce str1[x] ?? Un carattere..
  cout << "typeid(str1[0]): " << typeid(str1[0]).name() << endl; 

  //piu esplicito ..

  cout << "str1[0] e' tipo char? " << ( typeid(char) == typeid(str1[0]) ? "True" : "False" ) << endl; 

  //Overloading operatore +  (overloading si vedra' piu avanti..)
  //SI 
  cout << str1.substr(0, 5) + " pippo" << endl; 

  //SI
  cout << "pippo e' " + str1.substr(0, 5) << endl; 

  //NO!! 
  //cout << "pippo" + "paperino" << endl; 



}
