#include <iostream>
#include <iomanip>

using namespace std; 

int main(){


  unsigned int i=10; 

  cout << "DO-WHILE" << endl; 

  do{
    cout << "i=" << i << endl; 
  }while(i++<10); 


  cout << "WHILE" << endl; 

  i = 10;
  while(i++<10)
    cout << "i=" << i << endl; 


}
