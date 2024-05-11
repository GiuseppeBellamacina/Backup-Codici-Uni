#include <iostream>
#include <string>
#include <limits>

using namespace std;

/* 
* + controllo errore 
* + controllo EOF 
* + Scarta caratteri ``garbage''
*/

//End-Of-File
//Simulare EOF con i tasti CTRL+'d'
//NO LOOP
int main(){

  string s;
  float x;
  bool eof = false;

  //NB: In caso di EOF, ulteriori tentativi di lettura dallo stdin 
  //daranno altri EOF anche dopo cin.clear()! 

  //1.Primo input
  cout << "Insert any number: " << endl;
  cin >> x;

  //2. Potrebbe essere un End-Of-File..
  if((eof=cin.eof())){ //Da terminale: simulare un EOF con i tasti CTRL-D
    cout << "EOF! cin.eof()=" << cin.eof() << ", cin.fail()=" << cin.fail() << endl;
    cin.clear();
    cout << "EOF! cin.eof()=" << cin.eof() << ", cin.fail()=" << cin.fail() << endl;
    
  }

  //3.Controllo eventuali altri errori.
  else if(cin.fail()){
    //Non e' detto che se cin.eof() == 1 allora con.fail()==1 (dipende dall'implementazione)
    cerr << "IO error: cin.fail()=" << cin.fail() << ", cin.eof()=" << cin.eof() << endl;
    //reset stato di errore dello stream standard input
    cout << "Now clearing the iostate flags (eofbit, failbit, badbit)" << endl;
    cin.clear();
  }

  else 
    cout << "You entered: " << x << endl; 
   
   //scarta eventuale ulteriore input 
  if(!eof)
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
      
  if(!eof){ //Leggi NB all'inizio 
    //4.Secondo input.
    cout << "Now let's take some more input. Please insert a string" << endl;
    cin >> s; // se EOF prima, EOF anche adesso, nonostante clear() precedente..

    //5.Notifica errore 
    if(cin.eof())
      cerr << "EOF!" << endl;  
	
    else if(cin.fail()){ //some IO error!
      cerr << "IO error: cin.fail()=" << cin.fail() << endl;
    }

    else
      cout << "You entered: "  << s << endl;
  }
    cout << "Exit!" << endl;
}
