#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    int a[100], i;
    for(i=0; i<100; i++) a[i] = i;
    FILE *f;
    if ((f = fopen("file.bin", "rb")) == NULL){
        printf("Errore nell'apertura del file");
        exit(1);
    }
    int n = fread(a, sizeof(int), 100, f);
    for(i=0; i<n; i++) printf("a[%d]= %d\n", i, a[i]);
    fclose(f);
    return 0;
}