#include <iostream>

//OVERLOADING OPERATORE -> (possibili applicazioni: smart pointer)
using namespace std; 

class Y{

  int a;

  public:
    Y(int al){
      cout << "COS: Y()" << endl;
      a = al;
    }

    int getA(){
      cout << "Y::getA()" << endl;
      return a;
    }
};

class X{

  //unqualified == private
  Y* y;
  
  public:
   X(int alpha){y=new Y(alpha); }

  Y* operator->(){
    return y; 
  }  
  
};

int main(){

 X x(10); 

  //(x.operator->())->getA() 
 cout << x->getA() << endl;

}
