#include <iostream>
using namespace std;
class Contatore{
	private:
		int valore;
	public:
		Contatore(){
			valore = 0;
		}
		void incr(){
			++valore;
		}
		void v(){
			cout<<valore;
		}
		
};

int main(){
	Contatore a;
	for(int i=0; i<10; i++){
		a.incr();
	}
	a.v();
}
