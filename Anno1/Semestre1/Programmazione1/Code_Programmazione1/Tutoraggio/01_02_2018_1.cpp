#include <cstdlib>

#define N 10

/* 
int santone1(bool regione[][N]){ 

}
*/


int santone(bool **regione, int n){
  int i=n/2;
  int j=n/2;

  int libri_raccolti = 0;
  int r;

  while(i>=0 && j>=0 && i<n && j<n){
    if(regione[i][j]){
      libri_raccolti++;
      regione[i][j] = false;
    }

    r = rand()%4;
    switch(r){
      case 0:
	i--; 
	break; 
      case 1:
	i++;
	break; 
      case 2: 
	j++; 
	break; 
      case 3:
	j--; 
	break; 
    }
  } // end while 

  return libri_raccolti;  

}

int main(){

  // Codificare allocazione delle matrice quadrata di bool
  // riempire con elementi bool pseudo-casuali

  

  santone( .... ); 
  
  return 0; 
}
