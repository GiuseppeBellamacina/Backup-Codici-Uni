#include <iostream>
#include <string>
#include <limits>

using namespace std;

//Provare i segg input:
// 24.6 -- OK 
// 34lsls -- 34 sara' memorizzato, i restanti caratteri rimarranno nel buffer!
// alalala -- Errore rilevato, ma tutti i caratteri inseriti rimarranno nel buffer 
// + Controllo errore 
// - controllo EOF 
// - non si scartano eventuali caratteri inseriti dall'utente dopo la prima stringa!
int main(){

  float x =45; //floating point to collect the user input

  //1.Input
  cout << "Insert any number: " << endl; 
  cin >> x; 

  //2.Controllo eventuali errori.
  if(cin.fail()){ //some IO error!
    cerr << "IO error: cin.fail()=" << cin.fail() << endl; 
    //3.reset stato di errore dell'oggetto cin..
    cout << "Now clearing the error flags.." << endl;
    cin.clear(); 
    cout << "cin.fail()=" << cin.fail() << endl;
  }

   else
    cout << "The number you entered is " << x << endl; 

	cout<<"Riprova\n";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin>>x;
	if (cin.fail()){
		x=88;
	}
	cout<<x;

  //4. Now we are ready to take some more input and to check for
  //any error. But we should call ignore(.., '\n').. 
  return 0;

}
