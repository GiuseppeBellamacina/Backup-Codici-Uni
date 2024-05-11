#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

int main(int argc, char *argv[]){
    FILE *fp;
    char nomefile[50], ch;
    strcpy(nomefile, argv[1]); 
    if ((fp=fopen(nomefile, "r+"))==NULL){
        printf("Errore apertura file");
        exit(-1);
    }
    while(!feof(fp)){
        fscanf(fp,"%c",&ch);
        if ((ch<='z') && (ch>='a')){
            fseek(fp, ftell(fp)-1, SEEK_SET); // fseek(fp, -1, SEEK_CUR);
            fprintf(fp,"%c",ch+('A'-'a')); 
            fseek(fp, 0, SEEK_CUR);
        }
    }
    fclose(fp);
}