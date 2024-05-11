/*
    Funziona ma arriva a 9.8
    il file briscola.txt contiene 4 partite
    devono risultare 112, 148, 242 e l'altra boh, non 259
    c'è un errore nel calcolo del budget finale
    il file così fa funzionare solo le prime 3, l'ultima si sminchia
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>

#define N 100

using namespace std;

class Partita{
    private:
        int g, i, f, t, v, start, end, weight;
    public:
        Partita(int g, int i, int f, int t, int v) : g(g), i(i), f(f), t(t), v(v){
            start = g*24 + i;
            end = g*24 + f;
            weight = v-t;
        }

        int getStart(){return start;}
        int getEnd(){return end;}
        int getWeight(){return weight;}
        int getTar(){return t;}
        int getDay(){return g;}

        friend ostream& operator<<(ostream& out, const Partita& p){
            out << p.start << " " << p.end << " " << p.t << " " << p.weight << endl;
            return out;
        }
};

bool sortEnd(Partita a, Partita b) {
    return a.getEnd() < b.getEnd();
}

int p(vector<Partita> part, int i, int budget){ // trova l'attività compatibile più vicina a i
    if (i <= 0) return 0;
    for(int j=i-1; j>=0; j--){
        if((part[j].getEnd() <= part[i].getStart()) && (part[j].getTar() <= budget)){
            return j;
        }
    }
    return 0;
}

vector<int> opt(vector<Partita> part, int n, int budget){ // trova il valore ottimo
    vector<int> result(n+1); // vettore che contiene i valori ottimi
    result[0] = 0; // caso base
    for(int i=1; i<=n; i++){
        if (part[i].getTar() > budget){
            result[i] = result[i-1];
            budget -= result[i-1];
        }
        else{
            result[i] = max(part[i].getWeight() + result[p(part, i, budget)], result[i-1]);
            budget += result[i];
        }
    }
    return result;
}

int main() {
    system("cls");
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);

    for (int i=0; i<N; i++){
        int num;
        in >> num;
        int money;
        in >> money;
        vector<Partita> partite;
        for (int j=0; j<num; j++){
            int g, i, f, t, v;
            in >> g >> i >> f >> t >> v;
            Partita partita(g, i, f, t, v);
            partite.push_back(partita);
        }
        sort(partite.begin(), partite.end(), sortEnd);
        int k = 0;
        for(int d=0; d<=partite[num-1].getDay(); d++){
            Partita partita(-1, 0, 24, INT_MAX, 0);
            vector<Partita> tmp;
            tmp.push_back(partita);
            for(; k<partite.size(); k++){
                if (partite[k].getDay() == d)
                    tmp.push_back(partite[k]);
                else break;
            }
            vector<int> result = opt(tmp, tmp.size()-1, money);
            money += result[tmp.size()-1];
        }
        out << money << endl;
    }
    in.close();
    out.close();
    return 0;
}