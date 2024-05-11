#include <iostream>
#include <cstdlib>
using namespace std;

class Razionale {
	private:
  		int num,denom,segno;

  		int mcd(int a,int b){
  			return b == 0 ? a : mcd(b, a%b); //funzione ricorsiva mcd
  		}
  		
	public:
  		Razionale(int n){ //costruttore 1
  			num = n;
  			denom = 1;
  		}
  		
		Razionale(int n, int d){ //costruttore 2
  		int segno = 1;
 		 if(n * d < 0)
  			segno = -1;
 		 num = abs(n); //abs = val assoluto
 		 denom = abs(d);
 		 int c = mcd(num, denom);
 		 num = segno * num / c; //riduzione ai minimi termini
 		 denom = denom / c;
}//fine costruttore

int getNum(){return num;}
int getDen(){return denom;}

Razionale operator+(Razionale s){
  return Razionale(num*s.denom+denom*s.num,denom*s.denom);
}
Razionale operator-(Razionale s){
  return Razionale(num*s.denom-denom*s.num,denom*s.denom);
}
Razionale operator*(Razionale s){
  return Razionale(num*s.num,denom*s.denom);
}
Razionale operator/(Razionale s){
  return Razionale(num*s.denom,denom*s.num);
}

string toString(){
  char buffer[10];
  string st = itoa (num, buffer,10);
  st = st + "/" + itoa (denom, buffer,10);
  return st;
}//fine toString()
};//fine classe razionale

main(){
Razionale h(3,-2);
Razionale k(2,5);
cout<<h.toString()<<endl;//stampa -3/2
cout<<(h+k).toString();//stampa -3/2+2/5=-11/10
}//__________fine main
