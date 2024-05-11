#ifndef UTENTE_H // è come una if che controlla se è già definito UTENTE_H
#define UTENTE_H
#endif

#include <string>

class Utente{
	private:
		int id;
		std::string cognome;
		std::string nome;
		double pop;
		
	public:
		Utente();
		Utente(int _id,std::string _c,std::string _n,double _p);
		Utente(std::string s);
		
		int getId() const;
		std::string getCognome() const;
		std::string getNome() const;
		double getPopularity() const;
		
		bool operator>(const Utente&) const;
		bool operator==(const Utente&) const;
		bool operator!=(const Utente&) const;
		
		friend
		std::ostream& operator<<(std::ostream& out, const Utente& u);
		friend
		std::istream& operator>>(std::istream& input, Utente &user);
};
