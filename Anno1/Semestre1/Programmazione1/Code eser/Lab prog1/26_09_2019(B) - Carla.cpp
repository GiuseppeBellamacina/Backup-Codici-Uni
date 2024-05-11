#include <iostream>
#include <cstdlib>
#include <string>
#include <typeinfo>
#define DIM 10
using namespace std;

class A{ //classe astratta
	private:
		char *s; //stringa intesa come array di caratteri
		short len; //lunghezza array
	public:
		A(short m){ //costruttore
		this->len=m;
		s=new char[len];
		for(int i=0;i<len;i++)//trasformo i caratteri in int
		s[i]=(char)rand()%((int)'z'-(int)'a'+1)+(int)'a'; //inizializza s con lettere tra a e z
	}
		virtual double elab(short a)=0; //funzione virtuale pura, nessuna implementazione della funzione
		short getLen(){
			return len;
		}
		
	friend ostream& operator<<(ostream &s,A*);
	
	protected:
		char get(short i){
			return s[i%len]; //ritorna il carattere presente nell'indice i mod len
		}
};



class B:public A{
	private:
		int p;
	public:
		B(short m,int x):A(m){
			this->p=m;
		}
		double elab(short a){
			int v=0; //numero di vocali presenti nella stringa
			int c=0; //il numero di consonanti presenti nella stringa
			for(int i=0;i<getLen();i++){
				if(get(i)=='a' || get(i)=='e'|| get(i)=='i'|| get(i)=='o'||get(i)=='u')
				v++;
				else
				c++;
				}
				double r=(double)v/(double)(c+1);
				return r;
		}
     friend ostream& operator<<(ostream &s,A*);
	protected:
		bool test(){//restituisce true se almeno uno dei 4 caratteri all'inzio della stringa è una vocale
			for(int i=0;i<4;i++){
				if(get(i)=='a' || get(i)=='e'|| get(i)=='i'|| get(i)=='o'|| get(i)=='u')
				return true;
			}
			
		}
};

class C:public A{
	private:
		char x;
	public:
		C(short n,char c):A(n){
			this->x=c;
		}
		string g(char c){
			string xc=" ";
			xc+=x;
			return xc+c; //ritorana la stringa data dalla concatenazione del caraterre x e c
		}
		
		friend ostream& operator<<(ostream &s,A *);
		
	protected:
		double elab(short r){
			int num=0;
		for(int i=r%getLen(); i<getLen();i++){
			if((int)get(i)>=(int)x)
			num++;
		}
		double avg= (double)num/getLen();
		return avg;
	}
	
};

  ostream& operator<<(ostream &s,A* x){//overloading operatore <<
  	string str=" ";
  	for(int i=0;i<x->getLen();i++){
  		str+=x->s[i];
	  }
	  if(typeid(*x)==typeid(B))//typeid(*x).name() serve per mostrare il tipo(in questo caso B)
	  s<<")"<<typeid(*x).name()<<",s="<<str<<",p="<<((B*)x)->p<<",elab(3)="<<x->elab(3)<<endl;
	  else
	  if(typeid(*x)==typeid(C))
	  s<<")"<<typeid(*x).name()<<",s="<<str<<",p="<<((C*)x)->x<<",elab(3)="<<x->elab(3)<<endl;
	  
	  return s;
       	
  }

int main(){
	srand ( 111222333 );
	A** vett=new A*[DIM];
for ( int i =0; i<DIM; i++) {
short n=1+rand ()% 10;
     if ( rand ()%2==0)
    vett [i]= new B( n,rand()%10 + 1 ) ;
     else
     vett [i]= new C (n ,(char)(rand()%(( int )'z' - (int)'a' + 1 ) + ( int )'a')) ;

}

}
