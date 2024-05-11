#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;
class Utente{
    int ID;
    string cognome;
    string nome;
    double popolarita;
    public:
        void setID(int n){
            ID = n;
        }
        void setCognome(string n){
            cognome = n;
        }
        void setNome(string n){
            nome = n;
        }
        void setPopolarita(double n){
            popolarita = n;
        }
        int getID(){
            return ID;
        }
        string getCognome(){
            return cognome;
        }
        string getNome(){
            return nome;
        }
        double getPopolarita(){
            return popolarita;
        }
};
void selectionsort(Utente a[],int n){
    Utente temp;
    int i=0,j=0;
    int posminimo;
    for(int i=0;i<n-1;i++){
        posminimo=i;
        j=i+1;
        while(j<n){
            if(a[j].getPopolarita()<a[posminimo].getPopolarita())
                posminimo=j;
            j++;
        }
        temp = a[i];
        a[i]=a[posminimo];
        a[posminimo]=temp;
    }
}
void bubblesort(Utente a[],int n){
    Utente temp;
    bool scambio = true;
    while(scambio){
        scambio = false;
        for(int i=0;i<n-1;i++){
            if(a[i].getPopolarita()>a[i+1].getPopolarita()){
                temp = a[i];
                a[i] = a[i+1];
                a[i+1] = temp;
                scambio = true;
            }
        }
    }
}

int main()
{
    Utente utente[2000];
    ifstream input("utenti.txt",ios::in);
    for(int i=0;i<2000;i++){
        int ID;
        string cognome,nome;
        double popolarita;
        string riga;
        input>>riga;
        int l=riga.length();
        int j=0;string temp="";
        for(j=0;j<l;j++){
            if(riga[j]==';'){
            break;
            }
            temp+=riga[j];
        }
        ID=stoi(temp);
        temp="";
        riga.erase(0,j+1);
        l=riga.length();
        j=0;
        for(j=0;j<l;j++){
            if(riga[j]==';'){
            break;
            }
            temp+=riga[j];

        }
        cognome=temp;
        riga.erase(0,j+1);
        temp="";
        l=riga.length();
        j=0;
        for(j=0;j<l;j++){
            if(riga[j]==';'){
            break;
            }
            temp+=riga[j];
        }
        nome=temp;
        riga.erase(0,j+1);
        popolarita=stod(riga);

        utente[i].setID(ID);
        utente[i].setCognome(cognome);
        utente[i].setNome(nome);
        utente[i].setPopolarita(popolarita);
        }
        auto start = chrono::system_clock::now();
        //SELEZIONO L'ALGORITMO DI ORDINAMENTO DESIDERATO
        bubblesort(utente,2000);
        //selectionsort(utente,2000);
        auto end = chrono::system_clock::now();
        chrono::duration<double> elapsed = end - start;
        for(int i=0;i<2000;i++)
            cout<<utente[i].getID()<<" "<<utente[i].getCognome()<<" "<<utente[i].getNome()<<" "<<utente[i].getPopolarita()<<endl;
        cout << "Tempo trascorso: " << elapsed.count() << "s";

    return 0;
}
