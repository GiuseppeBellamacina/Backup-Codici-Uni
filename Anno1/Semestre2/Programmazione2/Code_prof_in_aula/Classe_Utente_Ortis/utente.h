#ifndef UTENTE_H
#define UTENTE_H


#include <string>

class Utente{
	int id;
	std::string cognome;
	std::string nome;
	double pop;

public:
	Utente();
	Utente(int _id, std::string _c, std::string _n, double _p);
	Utente(std::string s);

	bool operator>(const Utente&) const;
	bool operator==(const Utente&) const;
	bool operator!=(const Utente&) const;

	int getId() const;
	std::string getCognome() const;
	std::string getNome() const;
	double getPopularity() const;
	
friend
std::ostream& operator<<(std::ostream& out, const Utente& u);
friend
std::istream& operator>>(std::istream& input, Utente &user);

	
};

#endif