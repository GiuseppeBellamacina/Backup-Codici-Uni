#include <iostream>

using namespace std;

template <class T>
//oppure 
//template <typename T>
class Stack
  {
    private:

      int dimensione;     // Capacita' dello stack
      int top;            // Punta alla prima locazione libera
      T* ptr;            // Punta ai dati contenuti nello heap (T)

    public :
      Stack (int);
      ~Stack ();
      void Push (T); // T 
      T Pop(); // T 

  };


//Costruttore
template <class T> 
Stack<T>::Stack (int i)
  {
    dimensione = i;
    top = 0;
    ptr = new T [dimensione];
  }


//distruttore
template <class T>
Stack<T>::~Stack ()
  {
    delete [] ptr;
  }

//Mette un elemento in cima alla pila
template <class T>
void Stack<T>::Push (T dato)
  {
    if (top < dimensione)    
      ptr [top++] = dato;
  }

//Prende un elemento dalla cima della pila
template <class T>
T Stack<T>::Pop ()
  {
    if (!top)  return 0;

    return  ptr [--top];
  }

//Svuota lo stack o pila
template <class T>
void Svuota (Stack<T> & s) //non � una funzione classe membro, ma � globale
  {
    T dato;
    while (dato = s.Pop())
       cout << dato << '\n';
    cout << endl;
  }


int main ()
  {
  //avviene mappatura tra tipo generico e tipo reale
    Stack <int>   Interi (10);
    Stack <float> Reali (10);

    Interi.Push (3);
    Interi.Push (4);
    Interi.Push (5);
    Svuota (Interi);

    Reali.Push (1.1);
    Reali.Push (2.2);
    Reali.Push (3.3);
    Svuota (Reali);
    
    return 0;
  }


//*****************************************************************
//*****************************************************************
