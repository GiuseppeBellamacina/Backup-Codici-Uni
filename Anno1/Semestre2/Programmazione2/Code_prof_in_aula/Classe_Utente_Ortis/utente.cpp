#include "utente.h"
#include <iostream>
using namespace std;



Utente::Utente(){}
Utente::Utente(int _id, string _c, string _n, double _p):
			id(_id), cognome(_c), nome(_n), pop(_p) {}
//Utente(std::string s)


int Utente::getId() const {return id;}
string Utente::getCognome() const {return cognome;}
string Utente::getNome() const {return nome;}
double Utente::getPopularity() const {return pop;}

bool Utente::operator>(const Utente& u) const { return pop>u.getPopularity();}
bool Utente::operator==(const Utente& u) const { return pop==u.getPopularity();}
bool Utente::operator!=(const Utente& u) const {return pop!=u.getPopularity();}


ostream& operator<<(ostream& out, const Utente& u){
	out << u.pop << "\t-\t" << u.id << "\t" << u.cognome << endl;	
	return out;
}

istream& operator>>(istream& input, Utente &user){
	string id_string, pop_string;
	getline(input, id_string, ';');
	getline(input, user.cognome, ';');
	getline(input, user.nome, ';');
	getline(input, pop_string, '\n');
	user.id = stoi(id_string.c_str());
	user.pop = stod(pop_string.c_str());
	return input;
}

