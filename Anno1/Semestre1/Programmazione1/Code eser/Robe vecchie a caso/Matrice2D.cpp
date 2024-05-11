//MATRICE2D

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

class Mat2D{
	private:
		int n, m;
		static int r; //ci servirà per gestire il seme di RndInit
		double val;
		double** M;
	public:
		Mat2D(double value = 0.0, int n1 = 5, int m1 = 5) : val(value), n(n1), m(m1) //costruttore
		{
			M = new double* [n];
			for(int i = 0; i < n; i++){
				M[i] = new double [m];
				for(int j = 0; j < m; j++)
					M[i][j] = val;
			}
		}
		
		~Mat2D(){ //distruttore
			for(int i = 0; i < n; i++)
				delete [] M[i];
			delete [] M;
		}
		
		void Init(){ //inizializza manualmente (non è un costruttore, quindi va avviato dopo il costruttore)
			cout<<"Inserisci i valori:"<<endl;
			for(int i = 0; i < n; i++){
				for(int j = 0; j < m; j++){
					cout<<"["<<i<<"]["<<j<<"] = ";
					cin>>M[i][j];
					while(cin.fail()){
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout<<"["<<i<<"]["<<j<<"] = ";
						cin>>M[i][j];
					}
				}
			}
		}
		
		void RndInit(int x){ //inizializza con numeri casuali compresi tra 0 e x-1 (non è un costruttore, quindi va avviato dopo il costruttore)
			srand(time(0) + r);
			for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++)
				M[i][j] = rand()%x;
			}
			r++;
		}
		
		Mat2D operator + (const Mat2D& dx){ //overloading op +
			if(this -> n != dx.n || this -> m != dx.m){
				cout<<"ERRORE";
				return Mat2D (-1, 1, 1);
			}
			Mat2D sum(0, n, m);
			for(int i = 0; i < n; i++){
				for(int j = 0; j < m; j++){
					sum.M[i][j] = this -> M[i][j] + dx.M[i][j];
				}
			}
			cout<<"La somma e': "<<endl;
			return sum;
		}
		
		Mat2D operator - (const Mat2D& dx){ //overloading op -
			if(this -> n != dx.n || this -> m != dx.m){
				cout<<"ERRORE";
				return Mat2D (-1, 1, 1);
			}
			Mat2D dif(0, n, m);
			for(int i = 0; i < n; i++){
				for(int j = 0; j < m; j++){
					dif.M[i][j] = this -> M[i][j] - dx.M[i][j];
				}
			}
			cout<<"La differenza e': "<<endl;
			return dif;
		}
		
		Mat2D operator * (const Mat2D& dx){ //overloading op *
			if(this -> n != dx.n || this -> m != dx.m){
				cout<<"ERRORE";
				return Mat2D (-1, 1, 1);
			}
			Mat2D prd(0, n, m);
			for(int i = 0; i < n; i++){
				for(int j = 0; j < m; j++){
					prd.M[i][j] = this -> M[i][j] * dx.M[i][j];
				}
			}
			cout<<"Il prodotto e': "<<endl;
			return prd;
		}
		
		Mat2D operator / (const Mat2D& dx){ //overloading op /
			if(this -> n != dx.n || this -> m != dx.m){
				cout<<"ERRORE";
				return Mat2D (-1, 1, 1);
			}
			Mat2D quo(0, n, m);
			for(int i = 0; i < n; i++){
				for(int j = 0; j < m; j++){
					quo.M[i][j] = this -> M[i][j] / dx.M[i][j];
				}
			}
			cout<<"Il quoziente e': "<<endl;
			return quo;
		}
		
		void stampa(){ //stampa la matrice
			for(int i = 0; i < n; i++){
				for(int j = 0; j < m; j++){
					cout<<setw(10)<<setprecision(4)<<M[i][j];
				}
				cout<<endl;
			}
		}
};

int Mat2D::r = 0;

int main(){
	Mat2D a(1.18);
	Mat2D b(3.14);
	Mat2D c;
	Mat2D d;
	
	/*c.RndInit(11);
	d.RndInit(11);
	
	//c.Init();
	c.stampa();
	cout<<endl;
	d.stampa();
	(c+d).stampa();*/
	
	Mat2D sum = a + b;
	sum.stampa();
	
	cout<<endl;
	
	Mat2D dif = a - b;
	dif.stampa();
	
	cout<<endl;
	
	Mat2D prd = a * b;
	prd.stampa();
	
	cout<<endl;
	
	Mat2D quo = a / b;
	quo.stampa();
	
	cout<<endl;
	
	Mat2D sum1 = a + 2 + 3 + 4 - 10; //NB
	sum1.stampa();
	
	cout<<endl;
	
	Mat2D dif1 = a - 2;
	dif1.stampa();
	
	cout<<endl;
	
	Mat2D prd1 = a * 2;
	prd1.stampa();
	
	cout<<endl;
	
	Mat2D quo1 = a / 2;
	quo1.stampa();
}
