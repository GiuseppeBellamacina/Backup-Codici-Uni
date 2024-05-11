#include <sstream>
#include <iostream>

using namespace std; 

int main(){
  
  stringstream s; 
  int n = -1; 

  cout << "Inserisco 123.." << endl;
  s << 123 ; // numero

  cout << "Inserisco abab.." << endl;
  s << "abab"; //caratteri 

  //estraggo numero 

  cout << "Estraggo numero .." << endl; 
  s >> n; 

  if(s.eof()){
    cout << "EOF" << endl; 
    s.clear(); 
  }

  else if(s.fail()){
    cout << "fail" << endl;
    s.clear(); 
  }

  cout << "Estratto " << n << ", s=" << s.str() <<  endl; 

  //provo ad estrarre altro numero

  cout << "Estraggo numero .." << endl; 
  s >> n;

  if(s.eof()){
    cout << "EOF" << endl; 
    s.clear(); 
  }

  else if(s.fail()){
    cout << "fail" << endl;
    s.clear(); 
  }

  else
    cout << "Estratto " << n << ", s=" << s.str() <<  endl; 

  cout << "Inserisco 456.."; 
  s << 456 << endl;
  
  if(s.eof()){
    cout << "EOF" << endl; 
    s.clear(); 
  }

  else if(s.fail()){
    cout << "fail" << endl;
    s.clear(); 
  }

  else
    cout << "OK, s = " << s.str() << endl;

  string str; 
  cout << "Estraggo stringa .." << endl; 
  s >> str;

  if(s.eof()){
    cout << "EOF" << endl; 
    s.clear(); 
  }

  else if(s.fail()){
    cout << "fail" << endl;
    s.clear(); 
  }

  else
    cout << "Estratto " << str << ", s=" << s.str() <<  endl;  

}
