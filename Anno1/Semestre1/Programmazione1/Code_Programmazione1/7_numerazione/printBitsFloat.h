#include <iostream>

using namespace std; 

/* 
* Da rileggere dopo aver studiato i tipi, i puntatori e 
* le classi template..
*/
template<typename T> void printBitsFloat(T *ptr, size_t size){
  short S=1; 
  short E=9;
  if(typeid(T)==typeid(double))
    E=12;

  for(unsigned short int count = 0; count < size; count++){
	if(count==0 || count == S || count ==E )
	  cout << "| "; 
  	if((*ptr) & (1 << (size-count-1)))
	  cout << 1 << " ";
	else 
	  cout << 0 << " "; 		
  }

  cout << "|"; 
}
