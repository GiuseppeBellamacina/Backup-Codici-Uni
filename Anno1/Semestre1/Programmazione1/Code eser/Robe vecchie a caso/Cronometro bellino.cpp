#include<iostream>
#include<time.h>

using namespace std;
class C{
     int ti,tf;
public :
     void start();
     void stop();
     int print();
} ; //_________implemetazione metodi
void C::start(){
     ti=time(0) ;
     tf = 0 ;
}
void C::stop(){
     tf=time(0) ;
}
int C::print(){
     if (tf==0) return time(0)-ti ;
     else return tf-ti ;
}
main(){
char ch;
C p;
cout << "i] start\n";
cout << "f] stop\n";
cout << "p] print\n";
cout << "x] exit\n";
do {
cout << "opzione:";cin >> ch ;
ch=tolower(ch);
switch(ch) {
case 'i':p.start();cout << "orologio partito\n";break ;
case 'f':p.stop();cout << "orologio fermato\n";break ;
case 'p':cout << "tempo misurato:" << p.print() << endl;break ;
case 'x':break;
default:cout << "opzione non valida\n" ; }
}while(ch!='x');
}//__________fine main
