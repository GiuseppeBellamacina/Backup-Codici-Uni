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

bool decrescente(int a, int b){
    return a > b;
}

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);

    for(int i=0; i<N; i++){
        int elem, cap;
        in >> elem;
        in >> cap;
        vector<int> values(elem);
        for(int j=0; j<elem; j++){
            in >> values[j];
        }
        sort(values.begin(), values.end(), decrescente);
        int result = 0;
        for(int j=0; j<cap; j++){
            result += values[j];
        }
        out << result << endl;
    }
    in.close();
    out.close();
    return 0;
}