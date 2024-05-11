#include <string>
#include <cstring> // per la funzione strstr

using namespace std; 

//esercizio: 
bool func(char* **M, int n, int m, short a, short b, char *s){ 
//bool func(char* *M[], int n, int m, short a, short b, char *s){ 
  
  for(int j=0; j<m; j++){
    //controlla se la colonna di indice j ha il requisito 
    //descritto nell'esercizio 
    // ovvero se s e' contenuta in almeno a stringhe della colonna stessa
    // e non piu' di b stringhe della colonna stessa
    int counter=0; 
    for(int i=0; i<n; i++){
      // controllo se la stringa s e' contenuta nella stringa 
      // puntata da M[i][j]
      // EX: trasformare i tre if in unico if con le 
      // tre condizioni legate da end logico. 
      if(M[i][j]){  // se M[i][j] non e' null..
	if(strlen(s)<=strlen(M[i][j])){	
	  //EX: implementare un semplice algoritmo 
	  // per la ricerca di una occorrenza della stringa 
	  // puntata da s all'interno della stringa puntata da M[i][j]
	  // es: s[k] M[i][j][k]
	  if(strstr((const char*) M[i][j], (const char *) s)!=NULL)
	    counter++; 
	}
      }
    }

    if(counter >=a && counter <=b)
      return true; 
  } // for(j=...) 

  return false;  

}


int main(){

}
