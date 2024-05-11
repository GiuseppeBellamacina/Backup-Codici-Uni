#include <iostream>

using namespace std;

int main(){
    
  int kk=10;
  kk++; // add 1 to kk
  kk--; // subtract 1 from kk 
  kk+=10; // add 10 to kk. 
  kk=kk+10; //same as above

  cout << "kk=" << kk << endl; // 30 
  cout << "(kk--)=" << (kk--) << endl; // kk decrementato, ma stampo 30! 
  cout << "(--kk)=" << (--kk) << endl; // kk decrementato ulteriormente, stampo 28
  cout << "kk=" << kk << endl;

   return 0;

}
