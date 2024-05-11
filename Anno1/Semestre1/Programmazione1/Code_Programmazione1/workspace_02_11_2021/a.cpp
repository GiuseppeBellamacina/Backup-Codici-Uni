#include <iostream>
#include <iomanip>

#define N 10 

using namespace std; 

int main(){

  cout  << N << " iterazioni " << endl; 

  for(int i=0; i<=N; i++) // N-0 
    cout << "i=" << i << endl;

  cout  << (N+1) << " iterazioni " << endl; 

  for(int i=0; i<=N; i++) // N-0+1
    cout << "i=" << i << endl; 

}
