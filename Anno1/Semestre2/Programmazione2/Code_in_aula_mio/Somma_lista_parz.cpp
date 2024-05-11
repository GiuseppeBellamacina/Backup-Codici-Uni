//Ricosrsione
#include <iostream>
#define N 5

using namespace std;

//Sommare gli elementi di una lista

int listSum(int* vec, int i = N-1){ //somma i primi n elementi di un array
	if(n <= sizeof(vec) / sizeof(int)){
		if ( == 0) return 0;
		else if(n == 1) return vec[0];
		else{
			cout << "return " << vec[n-1] << " + listSum(vec, " << n-1  << ")"<< endl;
			return vec[n-1] + listSum(vec, n-1);
		}
	}
	else{
		cout << "ERRORE: fuori range" << endl;
		return -1;	
	}
}

int main(){
	int vec[] = {10,20,30,40,50};
	int res = listSum(vec, 5);
	cout << "Somma=\t" << res << endl;
	
	return 0;
}
