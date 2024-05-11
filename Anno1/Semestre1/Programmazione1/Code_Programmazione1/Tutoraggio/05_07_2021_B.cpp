/* Scrivere un metodo che prenda in input due matrici quadrate A e B di double di dimensioni n × n e restituisca in output
un array di bool di dimensione n. Sia r_i il rapporto tra il massimo valore degli elementi della riga i-esima di A ed il massimo
valore degli elementi della colonna i-esima di B. L’elemento i-esimo del vettore in ouput conterrà il valore booleano true se e
solo se 0 ≤ r_i ≤ 1 */

/* ESERCIZIO
* Codificare una funzione main per allocazione dei dati (random)
* -A allocazione dinamica
* -B allocazione automatica
*/ 

//1. allocazione automatica
//#define N 10 
//bool *func(double (*A)[N], double (*B)[N])
// bool *func(double A[][N], double B[][N])  
//2. allocazione dinamica
bool *func(double **A, double **B, int n){
// bool *func(double *A[], double *B[], int n)

  // allocazione del  vettore di output 
  bool *ret = new bool[n]; 

  for(int i=0; i<n; i++){
    // calcolare il max valore della riga i-esima di A
    // calcolare il max valore della col. i-esima di B
    // calcolare il rapporto r_i = MA_i/MB_i
    // controllare 0 <= r_i <= 1
    // inserire true o false in ret[i]
    double MA=A[i][0];
    double MB=B[0][i]; 
    double r;
    for(int j=1; j<n; j++){// calcolare MA_i e MB_i
	if(A[i][j]>MA)
	  MA=A[i][j];
	if(B[j][i]>MB)
	  MB=B[j][i];
    }

    // MA rappresenta il massimo valore della riga i di A
    // MB rappresenta il massimo valore della colonna i di B
    r = MA/MB;
    if(r<=1 && r>=0)
      ret[i] = true;
    else 
      ret[i] = false;
  }// end for(i=..)

  return ret;  	
}
