#include <iostream>

using namespace std;

class Div{
	private:
		int x;
		int y;
	public:
		Div(int); //costruttore
		int getX();
		int sqrtX();
		int* arrDiv();
};

Div::Div(int a){
	x = a;
}

Div::getX(){
	return x;
}

Div::sqrtX(){
	int n = 1;
	int m = n*n;
	int x2 = x*x;
	while(m <= x){
		n++;
		m = n*n;
	}
	y = --n;
	return y;
}

Div::*arrDiv(){
	int* ret = new int [y];
	//...
	return ret;
}

int main(){
	int a;
	cin>>a;
	Div d(a);
	cout<<d.getX()<<endl;
	cout<<d.sqrtX();
}
