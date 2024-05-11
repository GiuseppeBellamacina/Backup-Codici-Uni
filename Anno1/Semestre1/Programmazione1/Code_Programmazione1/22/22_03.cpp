#include <iostream>
#include <ctime>

using namespace std; 

class A{
  
    int x, y, z;
  
    public: 

      A(int a, int b, int c){
	x = a;
	y = b;
	z = c;
      }
      
      int getX(){
	return x; 
      }     

      int getY(){
	return y; 
      }
	  
	  int getZ(){
	return z; 
      }   

      void setX(int a){
       x = a; 
      }

      void sety(int b){
       y = b; 
      }
      
      void setz(int c){
       z = c; 
      }

}; 

int main(){
  
  //Ok, costruttore di conversione: {int,int}-> A(int,int) 
  A arr[10]={{1,2,101},{3,4,102},{5,6,103},{7,8,104},{9,10,105},{11,12,106},{13,14,107},{15,16,108},{17,18,109},{19,20,110}}; //OK
  //si provi:
  //A arr[10]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20}; //NO!

  for(int i=0; i<10; i++)
    cout << arr[i].getX() << " " << arr[i].getY() << " " << arr[i].getZ()<< endl;  
    
}
