#include <iostream>
#include <cstdlib>
using namespace std;

class Matrice2D{
	private:
		int n,m; //le due dimensioni della matrice
		int **matrix; //matrice2D
	public:
		
        Matrice2D(int n=4,int m=5){ 
			matrix=new int*[n]; //array di puntatori( n è il numero delle righe)
		for(int i=0; i<n;i++){
			matrix[i]=new int[m];  
		for(int j=0;j<m;j++)
		matrix[i][j]=rand()%8; //riempio la matrice di valori pseudo casuali
	    }
		this->n=n;
		this->m=m;
	}
	
	//metodo per somma che prende due parametri refeference e ritorna un reference
       Matrice2D &sumByRef(Matrice2D &m1,Matrice2D &m2){
        	Matrice2D *sum=new Matrice2D(m1.n,m1.m); //somma da restituire
        	
        	for(int i=0;i<n;i++){
        	for(int j=0;j<m;j++){
        	this->matrix[i][j]=m1.matrix[i][j] + m2.matrix[i][j];
		}
        	}
        	return *sum;
		}
	
	//operatore per overloading,funzione membro	
        Matrice2D operator +(const Matrice2D &m1){
			Matrice2D sum(n,m); //somma da restituire
        	
        for(int i=0;i<n;i++){
        	for(int j=0;j<m;j++){
        	sum.matrix[i][j]=this->matrix[i][j] + m1.matrix[i][j]; 
        }
        	}
        	return sum;
		}
		
	void stampa(){
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
			cout<<matrix[i][j]<<" ";
		}
		cout<<endl; 
		}
	}
	
    ~Matrice2D(){ //distruttore
		for(int i=0;i<n;i++){
			delete[] matrix[i];
		}
		delete[] matrix;
	} 
	
};

//ci vuole una somma a 0 0
		

int main(){
	Matrice2D a(4,5); //inizializzo i due oggetti
	Matrice2D b(4,5);
	
	Matrice2D &aR=a; //alias degli oggetti a e b
	Matrice2D &bR=b;
	Matrice2D sum(4,5);
	sum= aR.operator +(bR);
	sum.stampa();
}
