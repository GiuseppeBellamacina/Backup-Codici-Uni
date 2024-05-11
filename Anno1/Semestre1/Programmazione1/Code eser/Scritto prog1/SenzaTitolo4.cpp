#include <string>
#include <iostream>
using namespace std;

int main(){
	string res = "123456789";
	cout<<res<<endl;
	res.erase(2, 3);
	cout<<res;
}
