#include "Utente.h"
#include <iostream>

using namespace std;

Utente::Utente(){}
Utente::Utente(int _id,std::string _c,std::string _n,double _p):
	id(_id),cognome(_c),nome(_n),pop(_p){}
//Utente(std::string s);

int getId() const {return id;}
string getCognome() const; {return cognome;}
string getNome() const {return nome;}
double getPopolarity() const {return pop;}

bool Utente::operator>(const Utente& u) const {return pop>u.getPopularity();}
bool Utente::operator==(const Utente& u) const {return pop==u.getPopularity();}
bool Utente::operator!=(const Utente& u) const {return pop!=u.getPopularity();}

ostream& operator<<(ostream& out,Utente& u){
	out << u.pop<< "\t-\t" << u.id << "\t" << u.cognome << endl;		
}

istream& operator<<(istream& input,Utente& user){
	string id_string, pop_string;
	getline(input,id_string,';');
	getline(input,user.cognome,';');
	getline(input,user.nome,';');
	getline(input,pop_string,';');
	user.id = stoi(id_string.c_str());
	user.pop = stod(pop_string.c_str());
	return input;
}
