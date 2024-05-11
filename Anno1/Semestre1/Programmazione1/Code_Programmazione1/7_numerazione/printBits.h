#include <iostream>

using namespace std; 

/* 
* Da rileggere dopo aver studiato i tipi, i puntatori e 
* le classi template..
*/
template<typename T> void printBits(T *ptr, size_t size){
  for(unsigned short int count = 0; count < size; count++)
  	if((*ptr) & (1 << (size-count-1)))
	  cout << 1 ;
	else 
	  cout << 0; 		
}
