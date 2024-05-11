/* Scrivere un metodo che prenda in input tre parametri formali: una matrice di puntatori a stringhe A di
dimensioni n x m, uno short k ed una stringa s. Il metodo restituisca un array di bool di dimensione n in
cui il singolo elemento di indice i assume valore true se la stringa s e sottostringa di almeno k stringhe della
riga i-esima della matrice A.
*/ 

/* 
* ESERCIZIO: 
* 1. prototipo della funzione per matrice allocata dinamicamente
* 2. implementazione di un algoritmo che sostituisca la funzione find
* al fine di cercare una occorrenza di una stringa all'interno
* di un'altra stringa (uso dell'operatore [] per l'indicizzazione
* del singolo carattere dell'oggetto string)
* 3. completare con la codifica di una funzione main() per 
* allocazione dati 
*/ 

#define M 5
bool *func(string* A[][M], int n, short k, string s){
  
  bool *array = new bool[n];

  for(int i=0; i<n; i++){
    //1. contare il numero di stringhe
    // della riga di indice i della matrice A
    // che contengono la stringa s
    //2. confrontare tale numero con k 
    //3. assegnare di conseguenza un valore all'elemento array[i]
    unsigned counter = 0;
    // devo considerare tutti gli elem. A[i][x] (x=0...M-1)
    for(int x=0; x<M; x++){
      // s e' sottostringa della stringa puntata da A[i][x]? 
      //string::npos / std::cout 
      if(A[i][x]!=nullptr){ // esiste una stringa
	if(A[i][x]->length()>=s.length())
	  if((A[i][x]->find(s))!=string::npos) //s e' cont. in *A[i][x]
	  counter++; 
      }
    } // end for
    // counter conterra' il numero di stringhe della riga i 
    // che contengono almeno una occorrenza di s

    if(counter>=k)
      array[i] = true;
    else 
      array[i] = false; 
  } // end for(i=...)
  
  return array; 
}

