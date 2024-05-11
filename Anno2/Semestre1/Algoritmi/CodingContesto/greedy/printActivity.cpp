/*
    Il programma funziona perfettamente
    ma non è incluso nel coding contest
    Fatto da me
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#define N 10

using namespace std;

struct Activity {
    int start;
    int end;
};

bool sort_end(Activity a, Activity b) {
    return a.end < b.end;
}

void print_Activity(Activity a) {
    cout << a.start << " " << a.end << endl;
}

vector<int> greedy(vector<Activity> activities) {
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
    return result;
}

int main(){
    srand(time(NULL));
    vector<Activity> activities(N);
    for(int i=0; i<N; i++){
        activities[i].start = rand() % 24;
        activities[i].end = min(activities[i].start + rand() % 4, 24);
    }

    for(int i=0; i<N; i++)
        print_Activity(activities[i]);
    
    cout << "------------" << endl;

    sort(activities.begin(), activities.end(), sort_end);

    for(int i=0; i<N; i++)
        print_Activity(activities[i]);
    
    cout << "------------" << endl;
    
    vector<int> result = greedy(activities);
    for(int i=0; i<result.size(); i++)
        print_Activity(activities[result[i]]);
}