#include <string>
using namespace std;

string f1(string **A, int n, int m){
	string res = "";
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			int lunghezza1 = A[i][j].length();
			int lunghezza2 = A[i%n][j%m].length();
			if ((lunghezza1 - lunghezza2) > (i + j)){
				for(int k = 0; k < lunghezza1; k++){
					char c = A[i][j].at(k);
					switch(c){
						case 'a':
						case 'e':
						case 'i':
						case 'o':
						case 'u':
						case 'A':
						case 'E':
						case 'I':
						case 'O':
						case 'U':
							res+=c;
							break;
					}
				}
			}
		}
	}
	return res;
}

int main(){
}
