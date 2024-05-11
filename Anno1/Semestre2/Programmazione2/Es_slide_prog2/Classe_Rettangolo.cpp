#include <iostream>
#include <cmath>
using namespace std;

class Rettangolo{
	private:
		int base;
		int altezza;
		
	public:
		Rettangolo(int b=10, int h=5) : base(b), altezza(h){}
		
		int getBase(){return base;}
		int getAltezza(){return altezza;}
		void setBase(int n){base = n;}
		void setAltezza(int n){altezza = n;}
		
		int area(){return base*altezza;}
		int perimetro(){return (base+altezza)*2;}
		double diagonale(){return sqrt(pow(base,2)+pow(altezza,2));}
		
		bool isSquare(){return base==altezza ? true : false;}
};

int main(){
	Rettangolo a;
	cout << a.isSquare();
	
	return 0;
}
