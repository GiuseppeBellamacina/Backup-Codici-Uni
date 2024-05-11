#include <iostream>
using namespace std;

void f(int v[], unsigned short n){
  return; 
}

void g(int *v, unsigned short n){
  return;
}

void h(int **v, unsigned short n, unsigned short m){
  return; 
}

void k(int *v[], unsigned short n, unsigned short m){
  return;
}

void foo(int ***v, int n, int m, int l){
  return; 
}

void bar(int **q[], int n, int m, int l){
  for(int i=0;i<n;i++){
  	for(int j=0;j<m;j++){
  		for(int k=0;k<l;k++){
  			q[i][j][k] = 0;
		}
	}
  }
   for(int i=0;i<n;i++){
  	for(int j=0;j<m;j++){
  		for(int k=0;k<l;k++){
  			cout<<q[i][j][k]<<"  ";
		}
		cout<<endl;
	}
	cout<<endl;
  }
}


int main(){

  unsigned short n = 5; 
  unsigned short m = 10; 
  unsigned short l = 7; 

  int *v = new int[n]; // oppure int v[n]; 

  int **w = new int*[n]; // oppure int *w[n];
  for(unsigned short c = 0; c<n; c++)
    w[c] = new int[10];

  int ***z = new int**[n]; // oppure int** z[n];
  for(unsigned short c = 0; c<n; c++){
    z[c] = new int*[m];
    for(unsigned short j = 0;j<m; j++)
      z[c][j] = new int[l];
  }

  f(v, n); // array monodimensionale 
  g(v, n);

  h(w, n, m); //array bidimensionale 
  k(w, n, m); 

  foo(z, n, m, l); //array a tre dimensioni 
  bar(z, n, m, l); 
}
