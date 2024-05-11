#include <iostream>
#include <iomanip>
#include <climits>
#include <cmath>
#include <limits>
#include <bitset>

using namespace std;

int main()
{

  char a = 'x';

  //Quanto vale a? Intero con segno o senza segno?  
  cout << "Il carattere a: " << a << endl;  
  cout << "a=" << (int) a << endl;

  for(int start=(int) 'A'; start<(int) 'z'; start++)
    cout << " " << (char) start ; 
  cout << endl;  

  //quanto vale il carattere '~'? 
  cout << "~ ==" << (int) '~' << endl; 
  
} // end main()
