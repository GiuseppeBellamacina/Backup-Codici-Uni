#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <pthread.h>

void *measureFileSize(void *filename) {
    char *file = (char *)filename;
    FILE *fp = fopen(file, "rb");
    if (fp == NULL) {
        printf("Impossibile aprire il file %s\n", file);
        pthread_exit(NULL);
    }

    fseek(fp, 0, SEEK_END);
    long int fileSize = ftell(fp);
    printf("Dimensione del file %s: %ld bytes\n", file, fileSize);

    fclose(fp);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("Usage: %s <directory1> <directory2> ... <directoryN>\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        DIR *dir = opendir(argv[i]);
        if (dir == NULL) {
            printf("Impossibile aprire la directory %s\n", argv[i]);
            continue;
        }

        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type == DT_REG) { // Considera solo i file regolari
                char filepath[256];
                snprintf(filepath, sizeof(filepath), "%s/%s", argv[i], entry->d_name);

                pthread_t tid;
                if (pthread_create(&tid, NULL, measureFileSize, (void *)filepath) != 0) {
                    printf("Errore nella creazione del thread\n");
                    continue;
                }

                if (pthread_join(tid, NULL) != 0) {
                    printf("Errore nell'attesa del thread\n");
                    continue;
                }
            }
        }

        closedir(dir);
    }

    return 0;
}