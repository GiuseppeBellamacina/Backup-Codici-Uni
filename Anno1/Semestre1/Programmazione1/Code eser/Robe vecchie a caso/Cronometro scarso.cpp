#include <iostream>
#include <ctime>

using namespace std;

class C{
		int ti, tf;
	public:
		void start(){
			ti = time(0);
			tf = 0;
		}
		void stop(){
			tf = time(0);
		}
		void print(){
			cout<<tf-ti;
		}
};

int main(){
	C a;
	system("pause");
	a.start();
	system("pause");
	a.stop();
	a.print();
}
