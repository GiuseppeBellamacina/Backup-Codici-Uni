#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* find_min_index(int distances[6][6], int row, int n){
    int* min_index = malloc(n * sizeof(int));
    // copy the row of the matrix in a tmp array
    int tmp[6];
    for(int i = 0; i < 6; i++) tmp[i] = distances[row][i];
    // sort tmp with selection sort
    for(int i = 0; i < 6; i++){
        int min = i;
        for(int j = i + 1; j < 6; j++){
            if(tmp[j] < tmp[min]) min = j;
        }
        int tmp2 = tmp[i];
        tmp[i] = tmp[min];
        tmp[min] = tmp2;
    }
    // shift every element of tmp to left
    for(int i = 0; i < 6; i++) tmp[i] = tmp[i + 1];
    tmp[5] = 0;
    // find the indexes of the first n elements of tmp in the row of the matrix
    int j = 0;
    for(int i = 0; i < 6; i++){
        if(j == n) break;
        if(distances[row][i] == tmp[j]){
            min_index[j++] = i;
            i = -1;
        }
    }
    return min_index;
}

int main(int argc, char ** argv){
    int distances[6][6] = {
        {0, 10, 50, 100, 150, 200}, // C
        {10, 0, 90, 140, 190, 240}, // C++
        {50, 90, 0, 130, 180, 230}, // Java
        {100, 140, 130, 0, 170, 220}, // Python
        {150, 190, 180, 170, 0, 210}, // R
        {200, 240, 230, 220, 210, 0} // Matlab
    };
    int* min_index = find_min_index(distances,5 , atoi(argv[1]));
    for(int i = 0; i < atoi(argv[1]); i++) printf("%d ", min_index[i]);
    printf("\n");
    return 0;
}