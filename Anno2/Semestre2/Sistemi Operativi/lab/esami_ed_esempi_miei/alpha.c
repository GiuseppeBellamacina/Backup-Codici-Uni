#include "lib-misc.h" // libreria professore
#include <stdio.h> // input/output
#include <stdlib.h> // robe varie
#include <string.h> // manipolazioni di stringhe
#include <pthread.h> // per i thread
#include <semaphore.h> // per i semafori
#include <sys/mman.h> // per la mappatura
#include <sys/stat.h> // per fstat
#include <fcntl.h> // per i file
#include <ctype.h> // per tolower
#include <unistd.h> // per altre robe
//#include <dirent.h> // per le directory
//#include <signal.h> // per kill
//#include <sys/wait.h> // per wait/waitpid
//#include <sys/types.h> // per cose di stat

#define NUMBER_OF_THREADS 3

typedef enum{
    AL, MZ, P // nota bene, il thread Principale è alla fine
} thread_n;

typedef struct{
    char c;
    unsigned long stats[26]; // 26 lettere dell'alfabato
    int stop;
    sem_t sem[NUMBER_OF_THREADS];
} shared;

typedef struct{
    pthread_t tid;
    int number;
    shared* shared;
} t_data;

shared* init_shared(){
    shared *sh = malloc(sizeof(shared)); // alloco dinamicamente la memoria
    sh->stop = 0;
    memset(sh->stats, 0, sizeof(sh->stats)); // metto gli elementi dell'array a 0
    
    int err;
    if ((err = sem_init(&sh->sem[P], 0, 1) != 0))
        exit_with_err("Parent Semaphore Init", err);
    if ((err = sem_init(&sh->sem[AL], 0, 0) != 0))
        exit_with_err("AL Semaphore Init", err);
    if ((err = sem_init(&sh->sem[MZ], 0, 0) != 0))
        exit_with_err("MZ Semaphore Init", err);
    
    return sh;
}

void dealloc(shared* sh){
    for(int i=0; i<NUMBER_OF_THREADS; i++)
        sem_destroy(&sh->sem[i]);
    free(sh);
}

void *thread_func(void* args){
    int err;
    t_data *data = (t_data *)args;

    while(1){
        if((err = sem_wait(&data->shared->sem[data->number])) != 0)
            exit_with_err("thread sem_wait", err);
        
        // inizio sezione critica
        if(data->shared->stop) break;

        data->shared->stats[data->shared->c - 'a']++;
        // fine sezione critica

        if((err = sem_post(&data->shared->sem[P])) != 0)
            exit_with_err("thread sem_post", err);
    }
}

void print_data(shared* shared){
    for(int i=0; i<26; i++){
        printf("%c: %lu\t", i+'a', shared->stats[i]);
        if((i+1)%5 == 0) printf("\n");
    }
    printf("\n");
}

int main(int argc, char **argv){
    if(argc != 2){
        printf("utilizzo: %s <file>", argv[0]);
        exit(EXIT_FAILURE);
    }

    int err, fd; // roba per l'errore e file descriptor
    shared *sh = init_shared(); // devo creare la locazione di memoria condivisa
    t_data data[NUMBER_OF_THREADS-1]; // devo tenere traccia dei miei threads in qualche modo
    char *map; // per la mappatura del file
    struct stat s_file; // per avere la dimensione del file

    // occupiamoci dei threads
    for(int i=0; i<NUMBER_OF_THREADS-1; i++){
        data[i].number = i;
        data[i].shared = sh;

        if((err = pthread_create(&data[i].tid, NULL, thread_func, &data[i])) != 0)
            exit_with_err("Errore creazione thread", err);
    }

    // ora sistemiamo il file
    if((fd = open(argv[1], O_RDONLY)) == -1)
        exit_with_sys_err("Errore apertura file");
    
    if((err = fstat(fd, &s_file)) == -1)
        exit_with_err("Errore analisi file", err);

    if((map = mmap(NULL, s_file.st_size, PROT_READ, MAP_SHARED, fd, 0)) == MAP_FAILED)
        exit_with_sys_err("Errore mappatura file");

    if((err = close(fd)) == -1)
        exit_with_err("Errore chiusura file", err);

    // ora cominciamo a leggere il file
    for(int i=0; i<s_file.st_size; i++){
        if(tolower(map[i]) >= 'a' && tolower(map[i]) <= 'z'){
            // aspettiamo che nessuno thread secondario sia attivo
            if((err = sem_wait(&sh->sem[P])) != 0)
                exit_with_err("P wait", err);
            
            sh->c = tolower(map[i]);

            if(sh->c < 'l'){
                if((err = sem_post(&sh->sem[AL])) != 0)
                    exit_with_err("AL post", err);
            }
            else{
                if((err = sem_post(&sh->sem[MZ])) != 0)
                    exit_with_err("MZ post", err);
            }
        }
    }

    // aspettiamo la terminazione dell'ultimo thread
    // e comunico la fine del programma a tutti
    if((err = sem_wait(&sh->sem[P])) != 0)
        exit_with_err("P wait", err);

    sh->stop = 1;

    if((err = sem_post(&sh->sem[AL])) != 0)
        exit_with_err("AL post", err);
    if((err = sem_post(&sh->sem[MZ])) != 0)
        exit_with_err("MZ post", err);

    for(int i=0; i<NUMBER_OF_THREADS-1; i++){
        if((err = pthread_join(data[i].tid, NULL)) != 0)
            exit_with_err("Thread Join", err);
    }

    // rilascio la mappatura del file in memoria
    if ((err = munmap(map, s_file.st_size)) == -1)
        exit_with_err("Rilascio mappatura file", err);

    // stampo i dati ottenuti
    print_data(sh);
    
    // dealloco la memoria allocata dinamicamente
    dealloc(sh);

    exit(EXIT_SUCCESS);
}