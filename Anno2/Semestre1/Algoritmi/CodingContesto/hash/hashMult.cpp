// Fatto da me, funziona
#include <iostream>
#include <fstream>
#include <vector>
#include <typeinfo>

#define N 100

using namespace std;

template <class H>
class HashTable {
    private:
        int buckets;
        double c;
        vector<H>* table;
        int hash(H key) {
            double val;
            if (typeid(key) == typeid(double)) // if key is double
                val = key * c;
            else val = (int)key * c;
            val -= (int)val;
            return (int)(buckets * val);
        }
    public:
        HashTable(int m) : buckets(m), c(0.61803){
            table = new vector<H>[buckets];
        }
        void insert(H key) {
            int h = hash(key);
            table[h].push_back(key);
        }

        void print() {
            for (int i = 0; i < buckets; i++) {
                cout << i << ": ";
                for (int j = 0; j < table[i].size(); j++) {
                    cout << table[i][j] << " ";
                }
                cout << endl;
            }
        }
        
        void printSize(fstream& out) {
            for (int i = 0; i < buckets; i++) {
                out << table[i].size() << " ";
            }
            out << endl;
        }
};

int main(){
    fstream in, out;
    in.open("input.txt", fstream::in);
    out.open("output.txt", fstream::out);

    for(int i=0; i<N; i++){
        string type;
        int n, m;
        in >> type >> m >> n;
        if(type == "int"){
            HashTable<int>* ht = new HashTable<int>(m);
            for(int j=0; j<n; j++){
                int key;
                in >> key;
                ht->insert(key);
            }
            ht->printSize(out);
        }
        else if(type == "double"){
            HashTable<double>* ht = new HashTable<double>(m);
            for(int j=0; j<n; j++){
                double key;
                in >> key;
                ht->insert(key);
            }
            ht->printSize(out);
        }
        else if(type == "char"){
            HashTable<char>* ht = new HashTable<char>(m);
            for(int j=0; j<n; j++){
                char key;
                in >> key;
                ht->insert(key);
            }
            ht->printSize(out);
        }
        else if(type == "bool"){
            HashTable<bool>* ht = new HashTable<bool>(m);
            for(int j=0; j<n; j++){
                bool key;
                in >> key;
                ht->insert(key);
            }
            ht->printSize(out);
        }
    }
    in.close();
    out.close();
    return 0;
}