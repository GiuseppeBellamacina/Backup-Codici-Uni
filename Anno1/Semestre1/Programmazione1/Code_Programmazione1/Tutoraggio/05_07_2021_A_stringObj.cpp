/* Scrivere un metodo che prenda in input una matrice P di puntatori a caratteri di dimensioni n × m, un array di short senza
segno S ed un array di interi senza segno W entrambi di eguale dimensione l. Il metodo dia in output uno array di stringhe di
dimensione l il cui elemento i − esimo sia una stringa di lunghezza pari al valore i-esimo del vettore W , ed inoltre sia formato
da caratteri selezionati casualmente dalla riga di indice (S[i] mod n) della matrice P . NB: si presti attenzione ad eventuali
caratteri mancanti nella matrice P!
*/ 

/* 
* ESERCIZIO: 
* Codificare la funzione main(): 
* -A allocare dati nel free store per invocare la funzione 
* -B allocare dati localmente nella funzione main() per invocare la funzione con opportuno prototipo!!!
*/ 

// variante in cui si restituisce un array di oggetti string
string *func(char ***P, int n, int m, unsigned short *S, unsigned *W, int l){
// oppure 
//char *func(char ***P, int n, int m, unsigned short *S, unsigned *W, int l){

  string *ret = new string[l];
  
  for(int i=0; i<l; i++){ // costruire le stringhe dell'array ret
      int r = S[i]%n;

      // selezionare W[i] caratteri random dalla riga di indice r
      // W[i] iterazioni? 
      int j=0;
      while(j<W[i]){
	// prendo un carattere a caso dalla riga r di P 
	int z = rand()%m; // indice di colonna < m
	if(P[r][z]){ // P[r][z]!=nullptr ( o NULL)
	  // aggiungo il carattere puntato da P[r][z] alla stringa ret[i]
	  ret[i]+=*(P[r][z]); // operatore +=
	  j++; 
	}
      } // end while 
    } // end for 

    return ret;
} // end function 
