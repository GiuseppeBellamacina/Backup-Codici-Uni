#include <stdio.h>
#include <stdlib.h>

int main(void){
    FILE *f;
    char msg[80], n;
    f= fopen("testo.txt", "rb");
    if (f==NULL){
        printf("Errore nell'apertura del file");
        exit(1);
    }
    n = fread(msg, sizeof(char), 80, f);
    printf("%s", msg);
    fclose(f);
    printf("\n%d", n);
    return 0;
}