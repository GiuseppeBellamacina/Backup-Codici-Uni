/* Scrivere un metodo che prenda in input una 
matrice M di puntatori a double di dimensione n × m e 
due interi a e b e restituisca un array unidimensionale 
di booleani di lunghezza 2m tale che l’elemento 
dell’array di posizione 2i contiene True se e solo se la 
media dei soli elementi della colonna i-esima di M 
compresi tra a e b(estremi inclusi) è maggiore di 
(a+b)/2. 
Gli elementi dell’array di indice dispari devono
essere inizializzati a False.
 NB: Si presti attenzione ai numeri mancanti!
*/ 

bool *func(int a, int b, double ***M, int n, int m){

  bool *ret = new bool[2*m];
  for(int i=0; i<2*m; i++)
    ret[i] = false;

  for(int c=0; c<m; c++){ // m iterazioni
    // elaborazione/visita della colonna di indice c
    double avg = 0.0; 
    int count = 0; 
    for(int x=0; x<n; x++){ // n iterazioni
      //controllo dell'elemento *M[x][c]
      if(M[x][c]!=nullptr){
	double y = *M[x][c];
	if(y<=b && y>=a)
	  avg+=y; // somma
	  count++;  // incremento  del denominatore
	}
      } // end for (x=...) 
  
      if(count!=0)
	avg = avg/count;
  
      if(avg > ((double) (a+b))/2)
	ret[2*c] = true;  
    } // end for(c=...)
      
    return ret; 
  }
}
