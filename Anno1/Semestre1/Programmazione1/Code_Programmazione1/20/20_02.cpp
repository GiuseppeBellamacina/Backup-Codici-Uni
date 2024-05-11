#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <sstream>

using namespace std; 

int main(){ 

  cout << atoi("012") << endl; 
  cout << atoi("aa012") << endl; // output: 0. No controllo errore...
  cout << atoi("0") << endl; 
  cout << atoi("-12") << endl; 

  cout << atof("0.14") << endl; 
  cout << atoi("aa0.12") << endl; // output: 0. No controllo errore...
  cout << atof("0") << endl; 
  cout << setprecision(10) << atof("-12.123456") << endl; 

  stringstream ss;

  //Con stringstream meglio..

  float f1; 
  ss << "0.14";
  if(!(ss >> f1))
    cerr << "Error getting number from stringstream.." << endl; 
  else
    cout << "From stringstream: " << setprecision(6) << f1 << endl; 

  ss.str(""); 
  ss.clear(); 

  //In caso di errore..
  float f2; 
  ss << "a0.a14";
  if(!(ss >> f2))
    cerr << "Error getting  number from stringstream.." << endl; 
  else
    cout << "From stringstream: " << setprecision(6) << f2 << endl;
     
}
