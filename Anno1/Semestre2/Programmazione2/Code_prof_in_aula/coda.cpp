
#include <iostream>
using namespace std;

class Coda{
    int* arr;
    int capacita;
    int fronte;
    int fine;
    int count;

    int getFronte();
public:
    Coda(int size = 10);
    ~Coda();

    void dequeue();
    void enqueue(int x);
    int getSize() const;
    bool isEmpty()const;
    bool isFull()const;

    friend
    ostream& operator<<(ostream& out, const Coda& q);
};

ostream& operator<<(ostream& out, const Coda& q){
    out << endl << "Contenuto della coda:" << endl;
    int i=0;
    if(q.isEmpty())
        out << "coda vuota."<< endl;
    else{
        out << "<--";
        //for(i=q.fronte; i != q.fine+1; i = (i+1)%q.capacita)
        for(i=q.fronte; i != q.fine; i = (i+1)%q.capacita)
            out << "|" << q.arr[i];

        out << "|" <<q.arr[i]<< "|<--" << endl;
//        out << "|<--" << endl;


    out << "Rappresentazione interna:" << endl;
        for(int i = 0; i<q.capacita;i++){
            if(i==q.fronte)
                out << "fronte ->";
            else if(i==q.fine)
                out << "fine   ->";
            else
                out << "         ";
            out << i << " " << q.arr[i] << endl;
        }
        out << endl;
        return out;
        }
}


Coda::Coda(int size){
    arr = new int[size];
    capacita = size;
    fronte = 0;
    fine = -1;
    count = 0;
}
int Coda::getFronte(){
    if(isEmpty()){
        cout << "Coda vuota!!!" << endl;
        cout << "Operazione non riuscita." << endl;
        return -1;
    }
    else{
        return arr[fronte];
    }

}

Coda::~Coda(){ delete[] arr;}
void Coda::dequeue(){
    if(isEmpty()){
        cout << "Lista vuota!!!" << endl;
        cout << "Operazione non riuscita." << endl;
    }
    else{
        cout << "Rimuovo " << arr[fronte] << endl;
        fronte = (fronte +1)%capacita;
        count--;
    }
}
void Coda::enqueue(int x){
    if(isFull()){
        cout << "Coda piena!!!"<<endl;
        cout << "Operazione non riuscita."<<endl;
    }
    else{
        cout << "Inserisco " << x << endl;
        fine = (fine+1)%capacita;
        arr[fine] = x;
        count++;
    }
}
int Coda::getSize() const{ return count;}
bool Coda::isEmpty()const { return getSize()==0;}
bool Coda::isFull()const{ return getSize()==capacita;}

int main(){

    Coda q(5);

    q.enqueue(9);
    q.enqueue(8);
    q.enqueue(7);
    q.enqueue(6);
    q.enqueue(5);

    cout << q;

    q.dequeue();
    q.dequeue();
    q.enqueue(14);

    cout << q;
}


