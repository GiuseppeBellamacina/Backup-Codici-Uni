#include <iostream>
#include <cctype>
#include <limits>
#include <sstream>

using namespace std;

/*Scrivere una funzione di conversione che riceva come parametro una stringa
rappresentante una data in formato gg/mm/aa e la restituisca nel formato testuale, es:
17/11/91 --> 17 novembre 1991*/

bool check(string a){ // controlla se hai scritto bene
	if(a.length() != 8) // controlla se hai messo più o meno caratteri
		return true;
		
	for(int i = 0; i < a.length(); i++){ // controlla se tutti i caratteri sono numeri o '/'
		if(!isdigit(a[i]) && a[i] != '/')
			return true;
	}
	
	string mese = "";
	mese += a[3], mese += a[4];
	stringstream ss1;
	ss1 << mese;
	int num1;
	ss1 >> num1;
	if(num1 > 12 || num1 < 1) // controlla se il mese va bene
		return true;
	
	string day = "";
	day += a[0], day += a[1];
	stringstream ss2;
	ss2 << day;
	int num2;
	ss2 >> num2;	
	switch(num1){ // controlla se va bene il giorno in relazione al mese
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			if(num2 < 1 || num2 > 31)
				return true;
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			if(num2 < 1 || num2 > 30)
				return true;
			break;
		case 2:
			string aa = "";
			aa += a[6], aa += a[7];
			stringstream ss3;
			ss3 << aa;
			int num3;
			ss3 >> num3;
			if(num3 % 4 == 0){
				if(num2 < 1 || num2 > 29)
					return true;
			}
			else{
				if(num2 < 1 || num2 > 28)
					return true;
			}
	}
	return false;
}

string conv(string a){
	string ret = "";
	for(int i = 0; i < 2; i++)
		ret += a[i];
	string str1 = "";
	for(int i = 3; i < 5; i++)
		str1 += a[i];
	stringstream ss1;
	ss1 << str1;
	int n;
	ss1 >> n;
	switch(n){
		case 1:
			ret += " Gennaio ";
			break;
		case 2:
			ret += " Febbraio ";
			break;
		case 3:
			ret += " Marzo ";
			break;
		case 4:
			ret += " Aprile ";
			break;
		case 5:
			ret += " Maggio ";
			break;
		case 6:
			ret += " Giugno ";
			break;
		case 7:
			ret += " Luglio ";
			break;
		case 8:
			ret += " Agosto ";
			break;
		case 9:
			ret += " Settembre ";
			break;
		case 10:
			ret += " Ottobre ";
			break;
		case 11:
			ret += " Novembre ";
			break;
		case 12:
			ret += " Dicembre ";
	}
	string str2 = "";
	for(int i = 6; i < 8; i++)
		str2 += a[i];
	stringstream ss2;
	ss2 << str2;
	int m;
	ss2 >> m;
	if(m >= 0 && m <= 49)
		ret += "20" + str2;
	else if(m >= 50 && m <= 99)
		ret += "19" + str2;
	return ret;
}

int main(){
	string input = "";
	cout << "Inserisci una data nel formato gg/mm/aa: ";
	cin >> input;
	int err = 0;
	while(cin.fail() || check(input)){
		err++;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Hai scritto male, riprova" << endl << endl;
		if(err > 1)
			cout << "ATTENZIONE: devi scrivere anche gli eventuali 0" << endl
				 << "Es. 24/6/02 --> SBAGLIATO" << endl
				 << "    24/06/02 --> CORRETTO" << endl;
		cout << "Inserisci una data nel formato gg/mm/aa: ";
		cin >> input;
	}
	cout << "La data convertita e': " << conv(input);
}
