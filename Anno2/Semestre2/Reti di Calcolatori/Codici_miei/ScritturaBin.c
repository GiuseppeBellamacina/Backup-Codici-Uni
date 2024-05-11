#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    int a[100], i;
    for(i=0; i<100; i++) a[i] = i;
    FILE *f;
    if ((f = fopen("file.bin", "wb")) == NULL){
        printf("Errore nell'apertura del file");
        exit(1);
    }
    fwrite(a, sizeof(int), 100, f);
    fclose(f);
    return 0;
}