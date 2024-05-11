/*
    Il programma funziona perfettamente
    Fatto da me
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define N 100

using namespace std;

struct Activity {
    int start;
    int end;
};

bool sort_end(Activity a, Activity b) {
    return a.end < b.end;
}

int activity(vector<Activity> activities) {
    int n = activities.size();
    vector<int> result;
    result.push_back(0);
    int j = 0;
    for(int i=1; i<n; i++) {
        if(activities[i].start >= activities[j].end) {
            result.push_back(i);
            j = i;
        }
    }
    return result.size();
}

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);

    for(int i=0; i<N; i++) {
        int n_act;
        in >> n_act;
        vector<Activity> activities(n_act);
        for(int j=0; j<n_act; j++){
            char tmp;
            int t;
            Activity a;
            in >> tmp;
            in >> t;
            a.start = t;
            in >> t;
            a.end = t;
            in >> tmp;
            activities[j] = a;
        }
        sort(activities.begin(), activities.end(), sort_end);
        out << activity(activities) << endl;
    }
    in.close();
    out.close();
    return 0;
}