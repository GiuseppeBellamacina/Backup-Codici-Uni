#include <iostream>
#include <iomanip>
#include <climits>
#include <cmath>  //costanti e simboli matematici  
#include <limits>
#include <bitset>
#include <cstring>
#include <cfenv> // accesso alle funzioni/macro per i float 

/* 
* If set to on, the program informs the compiler that it might access 
* the floating-point environment to test its status flags (exceptions) 
* or run under control modes other than the one by default.
*/ 
#pragma STDC FENV_ACCESS ON

using namespace std;

int main()
{

  /* 
    Numeri in virgola mobile, float e double. 
  */ 
  float f1=-113.25; // precisione float == 6 ! 

  /* 
    RAPPRESENTAZIONE -- IEEE 754 
  */ 

  //Copiamo la sequenza di bit del numero in virgola 
  //mobile nel bitset
  static_assert(sizeof(float) == sizeof(unsigned int), "Incorrect size"); 
  unsigned f_int; 
  memcpy(&f_int, &f1, sizeof(f1)); // int <-- f1
  //Stampiamo la sequenza di bit che rappresenta il numero -113.25. 
  //Vedi slide 7_numerazione.pdf a pagina 53..
  //1 | 10100001 | 00000000000000011000101 
  cout << "Codifica IEEE 754 (32 bit) del numero " << f1 << endl; 
  cout << bitset<sizeof(float)*8>(f_int) << endl << endl;

  //Adesso con i double
  double d1=-113.25f; 
  //Copiamo la sequenza di bit del numero in virgola 
  //mobile nel bitset
  static_assert(sizeof(double) == sizeof(unsigned long int), "Incorrect size"); 
  unsigned long fl_int; 
  memcpy(&fl_int, &d1, sizeof(d1)); 
  //Stampiamo la sequenza di bit che rappresenta il numero 113.25. 
  //Vedi slide 7_numerazione.pdf a pagina 53..
  //Il Bias dello esponente nel caso dei double (11 bit exp) e' 1023. E=e+1023

  cout << "Codifica IEEE 754 (64 bit) del numero " << d1 << endl; 
  cout << bitset<sizeof(double)*8>(fl_int) << endl << endl;

  //Precisione: Numero p di cifre significative in base dieci.
  float f2 = 123456789*1.0f; // 9 cifre! 
  cout << setprecision(15) << "f2 (123456789)=" << f2 << endl;

  double d2 = 123456789123456789/1.0; // 18 cifre! 
  cout << setprecision(18) << "d2 (123456789123456789)=" << d2 << endl << endl;


  //Overflow
  std::feclearexcept(FE_ALL_EXCEPT);      
  double d3 = numeric_limits<double>::max(); 
  cout << "d3=" << setprecision(15) << d3 << endl;

  double pos_overflow = d3 * pow(10,10); 
  cout << "pos_overflow=" << setprecision(15) << pos_overflow << endl;

  //uso macro definita nello header cfenv  per rilevare overflow
  if(std::fetestexcept(FE_OVERFLOW))
        std::cout << "** overflow detected!\n\n";

  std::feclearexcept(FE_ALL_EXCEPT);      
  double neg_overflow = d3 * -pow(2,100); 
  cout << "neg_overflow=" << setprecision(15) << neg_overflow << endl;

  //uso macro per rilevare overflow -- header cfenv
  if(std::fetestexcept(FE_OVERFLOW)) 
        std::cout << "** overflow detected!\n\n";

  std::feclearexcept(FE_ALL_EXCEPT);  
  //Underflow   
  double d4 = numeric_limits<double>::min(); 
  cout << "d4=" << setprecision(15) << d4 << endl;
  cout << "underflow: " << d4*pow(10,-1) << endl; 

  //test: underflow? 
  if(std::fetestexcept(FE_UNDERFLOW)) 
        std::cout << "** underflow detected!\n\n";

  //<cmath> INFINITY, NaN
  cout << "+inf/-inf= " << -INFINITY/+INFINITY << endl;
  cout << "+inf/+inf= " << +INFINITY/+INFINITY << endl << endl;

  std::feclearexcept(FE_ALL_EXCEPT);
  // n/0 = ?? 
  cout << "1.0/0=" << 1.0/0 << endl; 
  cout << "-1.0/0=" << -1.0/0 << endl;

  //test: divisione per zero tra numeri in virgola mobile? 
  if(std::fetestexcept(FE_DIVBYZERO)) {
        std::cout << "** floating point division by zero!\n\n";
    } 

  //Approssimazione/troncamento del numero 0.1..
  double d5 = 0.1; 
  cout << setprecision(10) << "d5=" << d5 << endl; 
  cout << setprecision(15) << "d5=" << d5 << endl; 

  cout << "Ma..." << endl; 
  cout << setprecision(20) << "d5=" << d5 << endl;

  //Si provi a sommare il numero 0.1 dieci volte...
  float c = 0; 
  for(int i=0; i<10; i++)
    c+=0.1; 

  // c == 1.0 ?? Controlliamo.. 
  cout << setprecision(10) << c << "\n" ; 

  /* E la divisione per zero tra interi? */ 

 // cout << 1/0 << endl; //provare: il programma terminera' la sua esecuzione 
// (divisione per zero tra interi..), quindi la stringa "ciao" non sara' stampata
//

  cout << "ciao" << endl; 
  return 0;
} // end main()
