/*
    Il programma funziona perfettamente
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define N 100

using namespace std;

class Activity{
    private:
        int start;
        int finish;
        int weight;
    public:
        Activity(int s, int f) : start(s), finish(f){
            weight = finish - start;
        }

        int getStart(){return start;}
        int getFinish(){return finish;}
        int getWeight(){return weight;}
};

bool crescente(Activity a, Activity b){ // ordina le attività in base alla fine
    return a.getFinish() < b.getFinish();
}

int p(vector<Activity> activities, int i){ // trova l'attività compatibile più vicina a i
    for(int j=i-1; j>=0; j--){
        if(activities[j].getFinish() <= activities[i].getStart()){
            return j;
        }
    }
    return -1;
}

int opt(vector<Activity> activities, int n){ // trova il valore ottimo
    vector<int> result(n+1); // vettore che contiene i valori ottimi
    result[0] = 0; // caso base
    for(int i=1; i<=n; i++){
        result[i] = max(activities[i].getWeight() + result[p(activities, i)], result[i-1]);
    }
    return result[n];
}

int findSol(vector<Activity> activities, int n, int tmp=0){
    if (n == 0){
        return tmp;
    }
    else if (activities[n].getWeight() + opt(activities, p(activities, n)) > opt(activities, n-1)){
        tmp += activities[n].getWeight();
        return findSol(activities, p(activities, n), tmp);
    }
    else{
        return findSol(activities, n-1, tmp);
    }
}

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);

    for(int i=0; i<N; i++){
        int num;
        in >> num;
        vector<Activity> activities;
        Activity a(0, 0);
        activities.push_back(a);
        for(int j=0; j<num; j++){
            int start, finish;
            char tmp;
            in >> tmp;
            in >> start;
            in >> finish;
            in >> tmp;
            Activity b(start, finish);
            activities.push_back(b);
        }
        sort(activities.begin(), activities.end(), crescente);
        out << findSol(activities, activities.size()-1) << endl;
    }
    in.close();
    out.close();
    return 0;
}