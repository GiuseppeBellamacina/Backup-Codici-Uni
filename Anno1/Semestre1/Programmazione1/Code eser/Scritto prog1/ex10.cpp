#include <iostream>
#include <string>

using namespace std;

bool f1(string A[3][2], int n, int m, char C[1][2], int k, int z, short w){
	for(int i = 0; i < n; i++){
		string rigaA = ""; int counter = 0;
		for(int j = 0; j < m; j++){
			rigaA += A[i][j];
		}
		for(int j = 0; j < k; j++){
			string rigaC = "";
			for(int q = 0; q < z; q++){
				rigaC += C[j][q];
			}
			for(int q = 0; q < rigaA.length(); q++){
				for(int r = 0; r < rigaC.length(); r++){
					if(rigaA[q] == rigaC[r]){
						counter++;
						break;
					}
					else
						counter = 0;
				}
				if(counter >= w)
					return true;
			}
		}
		for(int j = 0; j < z; j++){
			string colonnaC = "";
			for(int q = 0; q < k; q++){
				colonnaC += C[q][j];
			}
			for(int q = 0; q < rigaA.length(); q++){
				for(int r = 0; r < colonnaC.length(); r++){
					if(rigaA[q] == colonnaC[r]){
						counter++;
						break;
					}
					else
						counter = 0;
				}
				if(counter >= w)
					return true;
			}
		}
	}
	for(int i = 0; i < m; i++){
		string colonnaA = ""; int counter = 0;
		for(int j = 0; j < n; j++){
			colonnaA += A[j][i];
		}
		for(int j = 0; j < k; j++){
			string rigaC = "";
			for(int q = 0; q < z; q++){
				rigaC += C[j][q];
			}
			for(int q = 0; q < colonnaA.length(); q++){
				for(int r = 0; r < rigaC.length(); r++){
					if(colonnaA[q] == rigaC[r]){
						counter++;
						break;
					}
					else
						counter = 0;
				}
				if(counter >= w)
					return true;
			}
		}
		for(int j = 0; j < z; j++){
			string colonnaC = "";
			for(int q = 0; q < k; q++){
				colonnaC += C[q][j];
			}
			for(int q = 0; q < colonnaA.length(); q++){
				for(int r = 0; r < colonnaC.length(); r++){
					if(colonnaA[q] == colonnaC[r]){
						counter++;
						break;
					}
					else
						counter = 0;
				}
				if(counter >= w)
					return true;
			}
		}
	}
	return false;
}

int main(){
	string D[3][2] = {"ciao", "cazzo", "bau", "miao", "bla", "blo"};
	char E[1][2] = {'i', 'a'};
	cout << f1(D, 3, 2, E, 1, 2, 2);
}
