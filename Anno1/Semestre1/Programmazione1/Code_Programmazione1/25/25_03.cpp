#include <iostream>

using namespace std; 

class ClasseX{

  //si provi ad inserire qui (riga 8) inizializzazione campo counter..
  static int counter;//variabile statica associata alla classe
  int x,y; //unqualified == private

  public:

    static int sum_x;
    static int sum_y; 

    ClasseX(int x, int y){
      this->x = x;
      this->y = y;

      sum_x+=x;
      sum_y+=y;
      counter++; 
    }

    //METODO STATIC (O DI CLASSE): ACCESSO AI SOLI ATTRIBUTI 
    //O METODI STATIC!!
    static int getCounter(){
      return counter; 
    }

    //metodo o funzione membro per accesso a campo static..
    int getTotal(){
      return counter; 
    }
};

//NB: 
// - static non inserito 
// - eccezione al data hiding (counter e' private)

//si provi a commentare una delle inizializzazioni
int  ClasseX::counter = 0;
int ClasseX::sum_x = 0;
int ClasseX::sum_y = 0;

int main(){

  ClasseX *clArr[10]; 

  for(int i=0; i<10; i++)
    clArr[i] = new ClasseX(i+1, i+2); 

  //Si provi a decommentare (Comp. error! counter is private...)
  //cout << ClasseX::counter << endl; 

  //metodo static usato per accesso a campo static 
  cout << "How many objects (by static method)? " << ClasseX::getCounter << endl; 
  //metodo non static usato per accesso a campo static
  cout << "How many objects (by non static method)? " << clArr[2]->getTotal() << endl; 

  //sum_x e sum_y public, accesso diretto! 
  cout << "sum_x=" << ClasseX::sum_x << ", sum_y=" << ClasseX::sum_y << endl;    

}
