#include <iostream>
#include <iomanip>

using namespace std; 

int main(){

  // 'z' ... 'a' // escluse le vocali 

  cout << "FOR-IF" << endl; 
  for(char c='z'; c>='a'; c--){
    if(c!='a' && c!='e' && c!='i' && c!='o' && c!='u') 
      cout << "C=" << c << endl; 
  }

  cout << "FOR-SWITCH" << endl; 
  for(char c='z'; c>='a'; c--){
    switch(c){
      case 'a':
      case 'e':
      case 'i':
      case 'o':
      case 'u':
	break;
      default:
	cout << "C=" << c << endl; 
    } 
  }

}
