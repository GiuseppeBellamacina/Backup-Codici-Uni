#include <iostream>

using namespace std;

int main(){
	int a = 0;
	cin >> a;
	cout << a << ": " << a <<", ";
	while(a > 1){
		if (!(a % 2)){
			a /= 2;
			cout << a << ", ";
		}
		else{
			a = 3 * a + 1;
			cout << a << ", ";
		}
	}
}
