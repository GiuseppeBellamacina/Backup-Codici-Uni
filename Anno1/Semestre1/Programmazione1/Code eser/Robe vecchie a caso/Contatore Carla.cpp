#include <iostream>
#define N 10
using namespace std;

/* Esercizio 1)Realizza una classe 'contatore' che contiene una variabile intera 'valore' come attributo e due metodi, 
il primo è un costruttore senza parametri che inizializza 'valore' a 0 il secondo incrementa semplicemente 
'valore ' di 1 tutte le volte che viene invocato. Esegui il test del programma con un ciclo for */

class Contatore{
	private:
		int valore;
	public:
	Contatore(); //costruttore
	Contatore operator++(int); //metodo per implementare il valore
	void stampa(); //serve a stampare i valori del contatore
		
};

Contatore::Contatore (){
	valore=0;
}

//operatore di incremento postfisso
Contatore Contatore::operator++(int){
	valore++;
	return *this;
}

void Contatore:: stampa(){
	cout<<valore<<endl;
}

int main(){
	Contatore c;
	for(int i=0;i<N;i++){
		c++;
		c.stampa();
	}
}
