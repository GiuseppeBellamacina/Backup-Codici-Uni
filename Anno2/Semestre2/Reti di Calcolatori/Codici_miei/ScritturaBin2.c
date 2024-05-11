#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    FILE *f;
    char msg[] = "Mia madre ingiuria le persone";
    f= fopen("testo.txt", "wb");
    if (f==NULL){
        printf("Errore nell'apertura del file");
        exit(1);
    }
    fwrite(msg, sizeof(char), strlen(msg)+1, f);
    fclose(f);
    return 0;
}