#include <iostream>

using namespace std;

// Uso di sizeof!! 

int main(){

   //How many bytes? It (partially) depends on the implementation. 
   cout << "bool       -> " << sizeof (bool) << endl;
   cout << "signed char  -> " << sizeof (signed char) << endl;
   cout << "unsigned char  -> " << sizeof (unsigned char) << endl;
   cout << "short int  -> " << sizeof (short int) << endl;
   cout << "int        -> " << sizeof (int) << endl;  
   cout << "unsigned int -> " << sizeof (unsigned int) << endl;
   cout << "long int   -> " << sizeof (long ) << endl;
   cout << "long long  -> " << sizeof (long long) << endl;
   cout << "float      -> " << sizeof (float) << endl;
   cout << "double     -> " << sizeof (double) << endl;
   cout << "long double-> " << sizeof (long double) << endl; 
   cout << "void *: " << sizeof(void *) << endl;

}
