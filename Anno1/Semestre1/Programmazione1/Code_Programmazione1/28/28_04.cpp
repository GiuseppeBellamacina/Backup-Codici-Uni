#include <iostream>
#include <cstdlib>

using namespace std;

//OPERATORI INCREMENTO / DECREMENTO
class Vettore3D
  {
    private :

       float    x, y, z;

    public:

       Vettore3D (float l=0.0, float m=0.0, float n=0.0) :
	      x(l), y(m), z(n)  
          { cout << " COS ";}

       void Visualizza (void) const
	   { cout << "( " << x << ", " << y << ", " << z << " )"; }

      //COMPILATORE OPERA DISTINZIONE TRA OPERATORE PREFISSO E POSTFISSO 
      //CON APPOSITA SINTASSI
        
	   Vettore3D &operator ++ ();  // PREFISSO: ++a
       Vettore3D operator ++(int); // POSTFISSO: a++; argomento "dummy" necessario per distinguere postfisso da prefisso), per overloading

       friend Vettore3D & operator -- (Vettore3D &);        // PREFISSO: --a
       friend Vettore3D operator -- (Vettore3D &, int);   // POSTFISSO: a--; int e' "dummy"

  }; //End class Vettore3D
  	   


//Vettore3D c = b++; // postfissa
//Vettore3D d = ++b; // prefissa

//1. Operatore unario PREFISSO implementato come MEMBRO
Vettore3D &Vettore3D::operator ++ ()
  {
    x++; 
    y++;
    z++;
    return *this; //OK, i tre numeri risulteranno incrementati, rest. una copia
  }


//2. Operatore unario POSTFISSO implementato come MEMBRO
Vettore3D Vettore3D::operator ++ (int) // int - parametro ``dummy'' si usa per distinguere le due versioni 
  {
    Vettore3D aux = *this; //aux e' una copia 
    x++; // incremento
    y++;
    z++;
    return aux; // x,y e z in aux sono invariati
  }

//3. Operatore unario PREFISSO implementato come "FRIEND" (NON-MEMBRO)
Vettore3D &operator -- (Vettore3D & operando)
  {
    operando.x--;
    operando.y--;
    operando.z--;
    return  operando;
  }


//4. Operatore unario POSTFISSO implementato come "FRIEND" (NON-MEMBRO)
Vettore3D operator -- (Vettore3D & operando, int) //int parametro dummy, si usa per distinguere le due versioni
  {
    Vettore3D aux = operando;
    operando.x--;
    operando.y--;
    operando.z--;
    return aux;
  }


int main ()

  {
    cout << "Creazione a(1,1,1), b, c" << endl; 

    Vettore3D a (1,1,1);
    Vettore3D b, c;

    cout << "\n\n";

    cout << "Visualizza a e b" << endl; 
    a.Visualizza();    b.Visualizza(); // a:(1,1,1), b:(0,0,0)
    cout << "\n\n";
  
    b = --a; // prefisso
    a.Visualizza();    b.Visualizza(); // a:(0,0,0) b:(0,0,0)
    cout << "\n\n";
    b = a--; //postfisso
    a.Visualizza();    b.Visualizza(); // a:(-1,-1,-1) b:(0,0,0)
    cout << "\n\n\n";

    cout << "b=(++a)++ ...\n";
    b = (++a)++; 
    a.Visualizza();    b.Visualizza();
    cout << "\n\n";

    cout << "b=(--a)-- ...\n";
    b = (--a)--; 
    a.Visualizza();    b.Visualizza();
    cout << "\n\n";

    //cout << "b=(a--)-- Questo ?? \n";
    //b=(a--)--;
    //ERR compilazione, (a--) non e' un reference, ma  
    //a.Visualizza();    b.Visualizza();
    //cout << "\n\n";
  
    return 0;
  }
//*****************************************************************
//*****************************************************************
