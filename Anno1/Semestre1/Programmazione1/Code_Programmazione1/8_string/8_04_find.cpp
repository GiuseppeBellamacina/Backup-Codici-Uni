#include <iostream>
#include <sstream>

using namespace std; 

int main(){

	stringstream ss; 
	ss << "test "; 
	ss << 123; 

	cout << ss.str() << endl; 

	int a = -1; 
	string out; 
	ss >> out; 

	cout << "out: " << out << endl; 

	ss >> a; 
	cout << "a: " << a;  

}
