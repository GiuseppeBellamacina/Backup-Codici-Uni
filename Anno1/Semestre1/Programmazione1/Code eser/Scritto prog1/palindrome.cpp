#include <iostream>
#include <string>
using namespace std;
int f1(string *A, int n){
	int max = 0;
	for(int i = 0; i < n; i++){
		int centro = A[i].length()/2;
		int counter = 0;
		for(int j = 0; j <= centro; j++){
			if (A[i][centro + j] == A[i][centro - j]){
				counter+=2; //alla prima iterazione il centro viene contato 2 volte, ma si risolve alla fine
			}
			else{
				break; //appena i caratteri sono diversi esce dal ciclo
				//j = centro + 1;
			}
		}
		if (max < counter){
			max = counter; //aggiorna il massimo
		}
	}
	return --max; //es: "aaa" � palindroma di dimensione 3, se faccio solo return max, output: 2,
					//se faccio return 2*max-1, output: 2*2-1 = 3 che � giusto
}

int main(){
	
	string **C = new string *[4];
	for (int i = 0; i < 4; i++)
		C[i] = new string [3];
		
	C[0][0] = {"porcabuttana"};
	cout<<C[0][0]<<endl;
		
	string *B = new string [3];
	B[0] = {"presenzanegativa"};
	B[1] = {"ottto"};
	B[2] = {"reepifanioinafipezr"}; //output: 15, senza il controllo dell'else, output: 17 (sbagliato)
	cout<<f1(B, 3);
}
