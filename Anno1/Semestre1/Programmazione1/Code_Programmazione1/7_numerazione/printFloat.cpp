#include <iostream>
#include <bitset>
#include <climits>

#include <cassert> 

#include "printBitsFloat.h"

using namespace std;

int main(){

  float x = -113.25;

  cout << "x = " << x << " = "; 

  //Controllare che sizoef(unsigned int) == sizeof(float)
  assert(sizeof(unsigned int) == sizeof(float)); 
  //In alternativa static_assert(sizeof(unsigned int) == sizeof(float));
  printBitsFloat<unsigned int>((unsigned int *)(&x), sizeof(x)*8);  

  cout << "\n";  
}
