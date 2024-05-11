#include <iostream>
using namespace std;

/*
iniziale: piolo da cui prende il piatto
centrale: piolo di appoggio
finale: piolo di destinazione del piatto
n: piatto da posizionare
*/

void hanoi(char iniziale, char centrale, char finale, int n){
	if (n == 1) //caso base
		cout << "Muovo il disco 1 dal piatto " << iniziale
			 << " al piatto " << finale << endl;
	else{
		//spostare n-1 dischi dal piolo inizale al centrale
		hanoi(iniziale, finale, centrale, n-1);
		cout << "Muovo il disco " << n
			 << " dal piatto " << iniziale
			 << " al piatto " << finale << endl;
		//spostare n-1 dischi dal centrale al finale...
		//... usando il piatto inizaile come ausiliario
		hanoi(centrale, iniziale, finale, n-1);
	}
}

int main(){
	int numDischi;
	cout << "Inserire un intero positivo: ";
	cin >> numDischi;
	if (numDischi <= 0) cout << "Numero non positivo" << endl;
	else{
		cout << "Con " << numDischi << " dischi,"
			 << " la sequenza di mosse e':" << endl;
		hanoi('A','B','C',numDischi);
	}
}
