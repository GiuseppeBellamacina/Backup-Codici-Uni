#include <iostream>

// per utilizzare la costante INT_MIN
#include <limits>


using namespace std;

// Soluzione 1: ricerca esaustiva
int sommaMassima1(int S[], int n){ // O(n^3)
    int _max = INT_MIN;
    int somma;
    for(int i=0;i<n;i++)  // O(n)
        for(int j=i;j<n;j++){  // O(n)
            somma = 0;
            for(int k=i;k<=j;k++) // O(n)
                somma = somma + S[k];

            if(somma > _max) _max = somma;
        }
    return _max;
}

//Soluzione 2:
/*se ho somma(S[i,j-1]) la sfrutto
  per calcolare somma(S[i,j]), infatti

  somma(S[i,j]) = somma(S[i,j-1]) + S[j]
  */
int sommaMassima2(int S[], int n){ // O(n^2)
    int _max = 0;
    int somma;
    // fisso l'elemento iniziale
    for(int i = 0;i<n;i++){ // O(n)
        somma = 0;
    // trovo la somma max fissato i, per i valori di j
        for(int j=i;j<n;j++){ // O(n)
            somma = somma + S[j];
            if(somma > _max) _max = somma;
        }
    }
    return _max;
}


/*
Soluzione 3: tra i segmenti di uguale lunghezza
solo uno puo' avere somma massima.
Parto da sx e considero un elemento per volta (una sola passata)
*/


int max_of(int a, int b) { return (a>b)? a:b;}
int max_of(int a, int b, int c) { return max_of(max_of(a,b),c);}



// Trovare la somma massima in arr[l...h] t.c. il segmento include arr[m]
int maxCrossingSum(int arr[], int l, int m, int h){

    // cerco nelle sequenze a sx di m
    int sum = 0;
    int left_sum = INT_MIN;
    for(int i=m; i>=l;i--){
        sum = sum + arr[i];
        if(sum > left_sum)
            left_sum = sum; // massimo a sx
    }

    // cerco nelle sequenze a dx di m
    sum = 0;
    int right_sum = INT_MIN;
    for(int i=m+1;i<=h;i++){
        sum = sum + arr[i];
        if(sum > right_sum)
            right_sum = sum;
    }

    // restituisco il massimo tra:
    // left_sum   right_sum   (left_sum+right_sum)
    return max_of(left_sum + right_sum, left_sum, right_sum);
}



int sommaMassima3(int S[], int n){
	int _max = 0;
	int somma= _max;
	for(int j = 0; j < n; j++) {
		if (somma > 0) {
			 somma = somma + S[j];
		} else {
			somma = S[j];
		}
		if (somma > _max) _max = somma;
	}
	return _max;
}

// restituisce la somma del segmento con somma massima
// all'interno di arr[l...h]
int maxSubarraySum(int arr[], int l, int h){

    // caso base: un solo elemento
    if(l == h) return arr[l];

    int m = (l+h)/2;

    /*
    Restituisco il massimo tra tre valori:
    a) max somma a sx di m
    b) max somma a dx di m
    c) max somma considerando sequenze che includono arr[m]
    */
    int a = maxSubarraySum(arr, l, m);
    int b = maxSubarraySum(arr, m+1, h);
    int c = maxCrossingSum(arr, l, m, h);

    return max_of(a,b,c);


}


int sommaMassimaRicorsiva(int S[], int n){
    return maxSubarraySum(S, 0, n-1);
}


int main(){
    int vec[] = {-7,4,-8,3,4,-2,6,-10,1,3,-3,9};
    //int vec[] = {2,2,2,2,2,2};

    int num = sizeof(vec)/sizeof(int);
    cout << "Somma max:\t" << sommaMassima1(vec,num) << endl;
    cout << "Somma max:\t" << sommaMassima2(vec,num) << endl;
    cout << "Somma max:\t" << sommaMassima3(vec,num) << endl;
    cout << "Somma max:\t" << sommaMassimaRicorsiva(vec,num) << endl;


    return 0;
}
