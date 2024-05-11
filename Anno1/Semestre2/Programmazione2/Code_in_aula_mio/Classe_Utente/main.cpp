#include "Utente.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define N 2000

#include <time.h>
#include <chrono>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::duration;
	
using namespace std;

void splitUserString(string str, string content[4]){
	char delim = ';';
	string token;
	stringstream ss(str);
	int i =0;
	
	while(getline(ss,token,delim)){
		content[i] = token;
		i++;
		if(i==4) break;
	}
}

int loadUsers(const string filename, Utente utenti[]){
	ifstream file;
	string line;
	string buff[4];
	file.open(filename);
	int num = 0;
	
	if(file.is_open()){
		while(getline(file,line)){
			splitUserString(line,buff);
			Utente u;
			u = Utente(stoi(buff[0]), buff[1], buff[2], stod(buff[3]));
			utenti[num] = u; // il costruttore di copia di default è pericoloso se gli attributi sono puntatori
			num++;
		}
		file.close();
	}
	else{
		cout << "Non posso aprire il file" << endl;
	}
	return num;
}

void stampaUtenti(Utente users[],int n, int maxval=10){
	cout << "Contenuto array:" << endl;
	if(n>maxval){
		for(int i=0; i<maxval/2; i++)
			cout << users[i];
		cout << "... " << endl;
		for(int i=n-maxval/2; i<n; i++){
			cout << users[i];
		}
	}
	else
		for(int i=0; i<n; i++)
			cout << users[i];
}

int readUsersFromStream(const string filename, Utente utenti[]){
	int num = 0;
	// utilizza il file di testo come input stream
	ifstream ifs(filename,ifstream::in);
	while(ifs.good()){
		Utente u;
		ifs>>u;
		utenti[num++]=u;
	}
	return num;
}

void insertionSort(Utente arr[], int n){
	int i,j;
	Utente key;
	for(i=0;i<n;i++){
		key = arr[i];
		j=i-1;
		while(j>=0 && arr[j]>key){
			arr[j+1] = arr[j];
			j--;
		}
		arr[j+1] = key;
	}
}

void scambia(Utente& a, Utente& b){
	Utente aux=a; 
	a = b; 
	b= aux;
}
void selectionSort(Utente arr[], int n){
	int i,j, min_idx;
	for(i=0;i<n;i++){
		min_idx = i;
		for(j=i+1;j<n;j++)
			if(arr[min_idx] > arr[j])
				min_idx = j;
		scambia(arr[min_idx], arr[i]);
	}
}

int main(){
	int n;
	
	//Soluzione 1: lettura da file mediante getline()
	Utente listaUtenti[N];
	n = loadUsers("utenti.txt", listaUtenti);
	//stampaUtenti(listaUtenti,n);
	
	cout << endl;
	//Soluzione 2: implemento un ifstream reader
	Utente listaUtenti2[N];
	n = readUsersFromStream("utenti.txt", listaUtenti2);
	//stampaUtenti(listaUtenti2,n);

	
	
	// Una volta implementato il comportamento dell'operatore >> per Utente, posso leggere tramite cin
	/*
	Utente u;
	cout << endl << "Inserisci un utente con valori separati dal punto e virgola: ";
	cin >> u;
	cout << u;
	*/
	
	
	
	auto t1 = high_resolution_clock::now();
	auto t2 = high_resolution_clock::now();
	duration<double, milli> ms_double;
	
	
	t1 = high_resolution_clock::now();
	insertionSort(listaUtenti,n);
	t2 = high_resolution_clock::now();
	ms_double = t2 - t1;
	cout << endl;
	cout << "Insertion Sort:" << endl;
	cout << "Tempo in ms:\t" << ms_double.count() << " ms" << endl;
	stampaUtenti(listaUtenti,n);
	
	
	t1 = high_resolution_clock::now();
	selectionSort(listaUtenti2,n);
	t2 = high_resolution_clock::now();
	ms_double = t2 - t1;
	cout << endl;
	cout << "Selection Sort:" << endl;
	cout << "Tempo in ms:\t" << ms_double.count() << " ms" << endl;
	stampaUtenti(listaUtenti2,n);


	return 0;
}
