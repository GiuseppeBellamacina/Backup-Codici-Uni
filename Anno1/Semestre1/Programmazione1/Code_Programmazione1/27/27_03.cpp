#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class Complex
  {
    private :

       float Re;
       float Im;

    public:

       Complex (float a, float b)
	  {
	    cout << "Costruttore (" << a << ", " << b << ")\n";
	    Re = a;
	    Im = b;
	  }
	

  }; //End class Complex


int main ()
  {
    Complex x(3.3, 5.0),   y(2.7, 3.14);
    //oppure..
    Complex x1{3.3, 5.0}; // invocazione costruttore..
    // Oppure...
    Complex z = Complex(2.0,2.0); // OK 

    /* NO, in quanto esiste un construttore ma NON esiste  un costruttore 
    * con un solo argomento (argomento standard oppure overloading)
    */ 
    //Complex z1{3.3}; 

    //Complex z2(); //NO! Non vi e' alcun costruttore di default!

    Complex z3 = x1; // Copia, OK 
    
}
