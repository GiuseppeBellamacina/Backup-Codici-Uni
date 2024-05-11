char ** metodo(char***M, int n, int m, unsigned *W, unsigned short *S, int l){

  char **ret = new char*[l];
  //ret[i] // punta ad una stringa lunga W[i]
  for(unsigned int i=0; i<l; i++)
    ret[i] = new char[W[i]];

  // creazione dei dati 
  for(unsigned int i=0; i<l; i++){
    int riga = S[i]%n;
   
    //la stringa di indice i viene riempita 
    // di caratteri selezionati casualmente 
    // dalla riga di indice `riga` della matrice M 
    int j=0;
    while(j<W[i]){
      int z = rand()%m;
      if(M[riga][z]){
	ret[i][j] = *M[riga][z];
	j++;
      }// end if
    }// end while
  }// end for (creazione dei dati)

  return ret; 
}
