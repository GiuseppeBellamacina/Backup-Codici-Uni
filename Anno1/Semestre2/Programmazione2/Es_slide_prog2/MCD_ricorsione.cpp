#include <iostream>

using namespace std;

int mcd(int a, int b){
	if(b == 0) return a;
	else{
		return mcd(b, a%b);
	}
}

int main(){
	cout << mcd(3, 818);
}
