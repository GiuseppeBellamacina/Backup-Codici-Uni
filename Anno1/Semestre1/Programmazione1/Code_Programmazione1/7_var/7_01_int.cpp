#include <iostream>
#include <iomanip>
#include <climits>
#include <cmath>
#include <limits>
#include <bitset>


using namespace std;

int main()
{
  /* Interi, letterali, overflow, rappresentazione in complemento a due. */ 

  //Un INTERO con un letterale intero
  int int1 = 234918743; // OK 

  //Overflow
  int int2 = 23491874399; // Overflow positivo. Segnalato dal compilatore? 
  cout << "int1: " << int1 << "\nint2: " << int2 << " (int2 dovrebbe essere " << 23491874399L << ").."  << endl; 

  //LONG..
  long long1 = 23491874399; // OK, no overflow
  cout << "\nlong1: " << long1 << endl;

  //uso di un letterale in forma esadecimale
  cout << "\nNow setting short1 and short2 as 0x" << std::hex << 0xffff << endl; 
  unsigned short short1 = 0xffff;
  //uso di un letterale in forma esadecimale per un intero corto CON SEGNO..
  //NB: RAPPRESENTAZIONE COMPLEMENTO A DUE...
  short short2 = 0xffff; // corrispondente valore decimale?   
  cout << "short1 (unsigned): " << std::dec <<  short1 << "\n short2 (signed): " << short2 << endl; 
  
  //From C++ 14 it is possible to provide literals 
  //as binary sequence  -- ob is prefix
  //Also available as Gnu GCC extension..

  // PREFISSO 0b ! 
  cout << "\nNow setting short3 and short4 as 0x" << std::hex << 0b1000000000000001 << " with binary literal.." << endl; 
  //Stampato in base dieci  senza segno 
  cout << "(unsigned) 10...0001= " << std::dec << 0b1000000000000001 << endl; 
  //Stampato in base dieci con segno.. 
  cout << "(signed) 10...0001= " <<  static_cast<short>(0b1000000000000001) << endl << endl; 

  //Assegnamento -- unsigned 
  unsigned short short3 = 0b1000000000000001; // BINARY LITERAL!
  //Assegnamento -- signed
  short short4 = 0b1000000000000001; 
  //Verifichiamo la rapresentazione in complemento a 2..
  //se lo short e' 2 byte, stampera' 32767 == -32768 + 1 = -2^(16-1) + 2^0 
  cout << "short3 (10...01) = " << short3 << endl; 
  cout << "short4 (10...01) = " << short4 << endl;

  //Stampare la sequenza di bit corrispondente ad una certa variabile
  //Classe ``template'' bitset. Le classi template saranno introdotte 
  //piu avanti..
  // Uso: bitset<>

  cout << "short4 in binario: " << bitset<sizeof(short)*8>(short4)  << endl << endl;

  // Valori booleani, true e false
  bool a = true; //letterale true 
  bool b = false; //letterale false

  //test
  if(a!=b)
    cout << "a diverso da b" << endl;
  else
    cout << "a uguale a b" << endl;

  //stampati come numeri interi, 0 o 1
  cout << "a=" << a << endl; 
  cout << "b=" << b << endl;

  //Divisioni tra interi
  cout << "3/2=" << 3/2 << endl; 

  //1/0=? 

  //cout << "1/0=" << 1/0 << endl; 

} // end main()
