#include <iostream>
#include <string>

using namespace std;

int funzione(string* **M, int n, int m, unsigned short k, unsigned short s) {
    int counter1 = 0;
    int counter2 = 0;
    int counter3 = 0;
    for (int j = 0; j < m; j++) {
        counter2 = 0;
        for (int i = 0; i < n; i++) {
            int lunghezza = M[i][j]->length();
            counter1 = 0;
            for (int k = 0; k < lunghezza; k++) {
                switch ((*M[i][j])[k]) {
                case 'a':
                case 'e':
                case 'i':
                case 'o':
                case 'u':
                    counter1++;
                    break;
                }
            }
            if (counter1 < s) {
                counter2++;
            }
        }
        if (counter2 >= k) {
            counter3++;
        }
    }
    return counter3;
}

int main() {

}
