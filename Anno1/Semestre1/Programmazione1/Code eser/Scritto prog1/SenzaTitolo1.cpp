bool f1(int*** A, int n, int m){
	int c1 = 0;
	int c2 = 0;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			c1++;
			c2 = 0;
			for(int h = 0; h < n; h++){
				for(int k = 0; k < m; k++){
					c2++;
					if(*A[i][j] == *A[h][k] && c1 < c2)
						return true;
					}
				}
			}
		}
		return false;
	}
	
int main(){
}
