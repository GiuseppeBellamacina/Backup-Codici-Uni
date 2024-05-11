#include <iostream>
#include <string>
#include <limits>

using namespace std;

/*
* Uso della funzione getline()
* DUE INPUT
* Nome, cognome
* numeri di telefono
* + controllo errore 
* + EOF
* NB: non esistono per definizione caratteri ``garbage'', non va invocato il metodo ignore()
*/
int main(){

  string nome_e_cognome; 
  string tel;
  bool end=false;
  bool eof=false;

  //NB: In caso di EOF, ulteriori tentativi 
  //di lettura da stdin leggeranno EOF anche dopo cin.clear()!

  //1.PRIMO INPUT, UN NUMERO, FINCHE' L'UTENTE 
  //NON INSERISCE UN NUMERO VALIDO! 
  while(!end && !eof){
    cout << "Inserisci nome e cognome: " << endl; 
    getline(cin, nome_e_cognome); // legge una intera linea di testo

    //eof will not end the loop!
    if(cin.eof()){
	cerr << "EOF!" << endl; 
	eof=true; 
	cin.clear();
    }

    //2.Controllo eventuali errori.
    else if(cin.fail()){ // IO error!
      cerr << "IO error: cin.fail()=" << cin.fail() << endl;
      eof=cin.eof();
      //3.reset stato di errore dell'oggetto cin..
      cerr << "Now clearing the error flags.." << endl;
      cin.clear(); 
      cerr << "cin.fail()=" << cin.fail() << endl;
      cout << "Invalid input!" << endl;
    }

    else{
      cout << "You entered: " << nome_e_cognome << endl; 
      end=true;
    }

    // no ignore! NB: getline() consuma l'intera linea fino al carattere '\n'
  }//end while

  end=false;

  //SECONDO INPUT, numero di telefono
  while(!end && !eof){
    //4. Now we are ready to take a string as input
    cout << "Insert phone number(s):" << endl;
    getline(cin, tel); // legge una intera linea di testo

    //5.Notifica errore 
    if(cin.fail()){ // IO error!
      cerr << "IO error: cin.fail()=" << cin.fail() << endl;
      cin.clear();
    }

    else{
      cout << "You entered:  " << tel << endl;
      end=true; // ok
    }

//      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignore the remaining chars
  }//end while
}
