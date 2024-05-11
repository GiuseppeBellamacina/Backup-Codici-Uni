#include <iostream>
#include <cstdlib>

using namespace std;

class Razionale{
	private:
		int num, denom, segno;
		
		int mcd(int x, int y){
			return y == 0 ? x : mcd(y, x%y);
		}
	
	public:
		Razionale(int n){
			num = n;
			denom = 1;
		}
		
		Razionale(int n, int d){
			num = n;
			denom = d;
			int segno;
				(n*d > 0) ? segno = 1 : segno = -1;
			num = abs(n);
 			denom = abs(d);
 			//minimi termini
 			int m = mcd(num, denom);
 			num = n * segno / m;
 			denom = d / m;
		}
		
		friend Razionale operator+(const Razionale a, const Razionale b);
		friend Razionale operator-(const Razionale a, const Razionale b);
		friend Razionale operator*(const Razionale a, const Razionale b);
		friend Razionale operator/(const Razionale a, const Razionale b);
		
	 string ToStr(){
			char str[10];
			string a = itoa(num, str, 10);
			a = a + '/' + itoa(denom, str, 10);
			return a;
		}
};

Razionale operator + (const Razionale a, const Razionale b){
	return Razionale(a.num*b.denom+a.denom*b.num, abs(a.denom*b.denom));
}

Razionale operator - (const Razionale a, const Razionale b){
	return Razionale(a.num*b.denom-a.denom*b.num, abs(a.denom*b.denom));
}

Razionale operator * (const Razionale a, const Razionale b){
	return Razionale(a.num*b.num, a.denom*b.denom);
}

Razionale operator / (const Razionale a, const Razionale b){
	return Razionale(a.num*b.denom, a.denom*b.num);
}

int main(){
	Razionale h(3,-2);
	Razionale k(2,5);
	cout<<h.ToStr()<<endl;//stampa -3/2
	cout<<(h+k).ToStr();//stampa -3/2+2/5=-11/10
}
