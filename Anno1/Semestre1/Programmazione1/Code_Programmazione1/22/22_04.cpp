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

}; 

int main(){
  
  A *arr[10];

  for(int i=0; i<10; i++)
    arr[i] = new A(2*i+1,2*i+2, 5);

  for(int i=0; i<10; i++){
    cout << arr[i]->getX() << " " << arr[i]->getY() << " " << arr[i]->getZ() << endl; 
  }
    
}
