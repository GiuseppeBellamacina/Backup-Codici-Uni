#include <iostream>
#include <cctype>
using namespace std;

int main(){
	string a = "Il criceto di Barbanera si chiamava Ettore";
	cout << a << endl << endl;
	
	//Scansione stringa (contiamo i caratteri maiuscoli)
	cout << "Scansione stringa (contiamo i caratteri maiuscoli):" << endl;
	int c = 0;
	for(int i=0; i<a.length(); i++)
		if(isupper(a[i])) // #include <cctype>
			c++;
	cout << "Il numero di lettere maiuscole di a e': " << c << endl;
	// si usa isupper() per i caratteri minuscoli
	// nel dubbio vedi pdf 20 da pag 26 a 28
	
	//Scansione matrice di puntatori a stringhe
	string*** M = new string** [2];
	for(int i=0; i<2; i++)
		M[i] = new string* [2];
		
	// Riempio la matrice direttamente da qui
	M[0][0] = new string("ciao");
	M[0][1] = new string("barbagianni");
	M[1][0] = new string("2e43d2");
	M[1][1] = new string("1234567");
	
	// Controlliamo se esiste una stringa che contiene SOLO numeri
	cout << endl << "Stringa di soli numeri: " << endl;
	for(int i=0; i<2; i++){
		for(int j=0; j<2; j++){
			c = 0;
			if(M[i][j]){ // il controllo del puntatore nullo qua non serve ma ovviamente all'esame lo devi mettere
				for(int k=0; k<M[i][j]->length(); k++){
					if(isalpha((*M[i][j])[k])){
						break;;
					}
					else c++;
				}
				if (c == M[i][j]->length())
					cout << "La stringa in posizione M[" << i << "][" << j << "] e' formata da soli numeri" << endl;
			}
		}
	}
	
	// Ricerca di sottostringa
	string s;
	cout << endl << "Ricerca sottostringa:" << endl;
	cout << "Inserisci stringa da cercare in a: ";
	cin >> s;
	if(a.find(s) != string::npos)
		cout << s << " e' contenuto in a e si trova a partire dall'indice " << a.find(s) << endl;
	else cout << "s non e' contenuto in a" << endl;
	
	// Estrazione sottostringa (non viene eliminata dalla stringa principale)
	cout << endl << "Estrazione sottostringa:" << endl;
	cout << a << endl;;
	cout << "Estraiamo una parte:" << endl;
	cout << a.substr(24, 11) << endl; // il primo parametro è l'indice dal quale si inizia a estrarre
						   // il secondo parametro è la lunghezza della sottostringa da estrarre (se non lo metti la estrai fino alla fine)
	
	// Eliminazione sottostringa
	cout << endl << "Eliminazione sottostringa:" << endl;
	cout << a << endl;
	cout << "Eliminiamo una parte:" << endl;
	a.erase(0,14); // la stessa cosa dei parametri vale anche qui
	cout << a;
	
	return 0;
}
