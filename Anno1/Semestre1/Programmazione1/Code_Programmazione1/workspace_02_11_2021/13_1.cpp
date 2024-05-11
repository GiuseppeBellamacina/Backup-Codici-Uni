#include <limits>
#include <iostream>

using namespace std; 

int main(){

  double x = -1;
  string s;

  cout << "Please enter a number: " << endl; 
  if((cin >> x))
    cout << x << endl; 
  else if(cin.eof())
    cerr << "EOF! " << endl; 
  else if(cin.fail()){
    cin.clear(); 
//    getline(cin, s); // consumare l'input nel buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Last trial! Please enter a number: " << endl;
    cin >> x; 
    cout << "x=" << x << endl;     
  }  
}
