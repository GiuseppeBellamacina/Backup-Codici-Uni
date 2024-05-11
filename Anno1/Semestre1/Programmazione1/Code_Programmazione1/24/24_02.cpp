#include <iostream>

using namespace std; 

class VettoreInt{
  int *arr;  

  public: 
    VettoreInt(int n){
      arr = new int[n];
      for(int i=0; i<n; i++)
	arr[i] = i+1; 
    }

    int &getElem(int i){
      return arr[i]; 
    }

  /*  
    void setElem(int i, int v){
      arr[i] = v;
    }
  */
};

int main(){

  VettoreInt myVec(10);

  cout << myVec.getElem(2) << endl;  

  cout << "myVec.getElem(4)=" << myVec.getElem(4) << endl; 
  //NB: risultato di getElem() usato 
  //nella parte sinistra di un assegnamento 
  myVec.getElem(4) = 18;   

  cout << "myVec.getElem(4)=" << myVec.getElem(4) << endl; 
}
