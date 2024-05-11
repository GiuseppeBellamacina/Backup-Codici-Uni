//� un puntatore che punta ad un puntatore di caratteri
//nella seconda parte, il tipo � char *, i due altri ** indicano la matrice M
//M � un char *** in cui ogni elemento di ** � uno char * (che punta ad un char)
char ** metodo(char ***M, int n, int m, unsigned *W, unsigned short *S, int l){
	char ** ret = new char*[l];
	//ret � un array di puntatori a caratteri
	//ret[i] punta ad una stringa lunga W[i]
	for(unsigned int i = o; i < l; i++)
		ret[i] = new char[W[i]];
	//creazione dei dati
	for(unsigned int i = o; i < l; i++){
		int riga = S[i]%n;	
		int j = 0
		while(j < W[i]){
			int z = rand()%m;
			if(M[riga][z]){
				ret[i][j] = *M[riga][z];
				j++;
			}//end if	
		}//end while
	}//end for
	return ret;
}
