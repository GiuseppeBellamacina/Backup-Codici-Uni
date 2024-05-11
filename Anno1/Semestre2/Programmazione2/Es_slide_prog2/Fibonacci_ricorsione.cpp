#include <iostream>

using namespace std;

int Fib(int n){
	int primo = 0, secondo = 1, aux;
	if(n <= 1) return n;
	else{
		return Fib(n-1) + Fib(n-2);
	}
}

int main(){
	for(int i = 0; i < 150; i++)
		cout << Fib(i) << endl;
}
