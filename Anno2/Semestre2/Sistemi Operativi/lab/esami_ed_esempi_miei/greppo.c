#define _GNU_SOURCE
#include "../lib/lib-misc.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <unistd.h>
#include <linux/limits.h>

#define BUFFER_SIZE 1024

typedef struct{
    // riga letta
    char buffer[BUFFER_SIZE];
    // path del file letto
    char pathfile[PATH_MAX];
    // true se il reader ha terminato
    bool done;
    // 0 se tocca a filterer, altrimenti thread_n
    int turn;
    // numero totale di reader
    int nreader;

    //semaforo mutex
    pthread_mutex_t mutex;
    // una variabile cond per ogni thread che condivide shared_rf
    pthread_cond_t *cond;
} shared_rf;

shared_rf *init_shared_rf(int n){
    shared_rf *rf = malloc(sizeof(shared_rf));
    rf->done = 0;
    rf->turn = 1; // così comincia il primo reader
    rf->nreader = n;
    int err;
    if((err = pthread_mutex_init(&rf->mutex, NULL)) != 0)
        exit_with_err("pthread_mutex_init", err);
    rf->cond = malloc(sizeof(pthread_cond_t) * (n+1));
    for(int i=0; i<=n; i++){
        if((err = pthread_cond_init(&rf->cond[i], NULL)) != 0)
            exit_with_err("pthread_cond_init", err);
    }
    return rf;
}

void destroy_shared_rf(shared_rf *rf){
    pthread_mutex_destroy(&rf->mutex);
    for(int i=0; i<=rf->nreader; i++)
        pthread_cond_destroy(&rf->cond[i]);
    free(rf->cond);
    free(rf);
}

typedef struct{
    // riga letta
    char buffer[BUFFER_SIZE];
    // path del file letto
    char pathfile[PATH_MAX];
    // true se filterer ha terminato
    bool done;
    // 0 se tocca a filterer, altrimenti a writer
    int turn;

    //semaforo mutex
    pthread_mutex_t mutex;
    // una variabile cond per filterer e una per writer
    pthread_cond_t cond[2];
    // barriera per sincronizzare il termine dei lavori
    pthread_barrier_t barrier;
} shared_fw;

shared_fw *init_shared_fw(){
    shared_fw *fw = malloc(sizeof(shared_fw));
    fw->done = fw->turn = 0;
    int err;
    if((err = pthread_mutex_init(&fw->mutex, NULL)) != 0)
        exit_with_err("pthread_mutex_init", err);
    for(int i=0; i<2; i++){
        if((err = pthread_cond_init(&fw->cond[i], NULL)) != 0)
            exit_with_err("pthread_cond_init", err);
    }
    if((err = pthread_barrier_init(&fw->barrier, NULL, 3)) != 0)
            exit_with_err("pthread_barrier_init", err);
    return fw;
}

void destroy_shared_fw(shared_fw *fw){
    pthread_mutex_destroy(&fw->mutex);
    for(int i=0; i<2; i++)
        pthread_cond_destroy(&fw->cond[i]);
    pthread_barrier_destroy(&fw->barrier);
    free(fw);
}

typedef struct{
    pthread_t tid;
    int thread_n;
    char *word;
    char *filepath;
    bool iFlag;
    bool vFlag;

    shared_rf *rf;
    shared_fw *fw;
} thread_data;

bool share_line(thread_data *td, char *map){
    int err;
    char *line;
    bool ret = 1;

    if ((err = pthread_mutex_lock(&td->rf->mutex)) != 0)
        exit_with_err("pthread_mutex_lock", err);
    
    // fino a quando non è il turno del reader
    while (td->rf->turn != td->thread_n)
        if ((err = pthread_cond_wait(&td->rf->cond[td->thread_n], &td->rf->mutex)) != 0)
            exit_with_err("pthread_cond_wait", err);
    
    // condividiamo una riga alla volta
    if((line = strtok(map, "\n")) == NULL){
        ret = 0;
        td->rf->done = 1;
    }
    else{
        strncpy(td->rf->buffer, line, BUFFER_SIZE);
        strncpy(td->rf->pathfile, td->filepath, PATH_MAX);
    }

    // il reader ha terminato il turno
    td->rf->turn = 0;

    if ((err = pthread_cond_signal(&td->rf->cond[0])) != 0)
        exit_with_err("pthread_cond_signal", err);

    if ((err = pthread_mutex_unlock(&td->rf->mutex)) != 0)
        exit_with_err("pthread_mutex_unlock", err);

    return ret;
}

void *reader(void *args){
    thread_data *td = (thread_data *)args;
    int err, fd;
    char *map;
    struct stat st;

    if((fd = open(td->filepath, O_RDONLY)) == -1)
        exit_with_sys_err("open");
    
    if(fstat(fd, &st) == -1)
        exit_with_sys_err("fstat");
    
    if((map = mmap(NULL, st.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
        exit_with_sys_err("mmap");
    
    if(close(fd) == -1)
        exit_with_sys_err("close");
    
    share_line(td, map);
    while(share_line(td, NULL));

    munmap(map, st.st_size);
    pthread_exit(NULL);
}

bool is_valid(thread_data *td, char *line){
    char *word = NULL;

    if(td->iFlag)
        word = strcasestr(line, td->word);
    else
        word = strstr(line, td->word);

    if (td->vFlag)
        return word == NULL;
    else
        return word != NULL;
}

void *filterer(void *args){
    int err;
    thread_data *td = (thread_data *)args;
    unsigned actual_reader = 1;
    char *line = NULL;
    char buffer[BUFFER_SIZE];
    char file[PATH_MAX];

    while(1){
        if ((err = pthread_mutex_lock(&td->rf->mutex)) != 0)
            exit_with_err("pthread_mutex_lock", err);

        // se non è il turno del filterer
        while (td->rf->turn != 0)
            if ((err = pthread_cond_wait(&td->rf->cond[0], &td->rf->mutex)) !=0)
                exit_with_err("pthread_cond_wait", err);
        
        if(td->rf->done){
            actual_reader++;
            // tutti i reader hanno terminato
            if(actual_reader > td->rf->nreader) break;

            // diciamo al prossimo reader che può iniziare
            td->rf->done = 0;
            td->rf->turn = actual_reader;

            if ((err = pthread_cond_signal(&td->rf->cond[actual_reader])) !=0)
                exit_with_err("pthread_cond_signal", err);

            if ((err = pthread_mutex_unlock(&td->rf->mutex)) != 0)
                exit_with_err("pthread_mutex_unlock", err);

            continue;
        }
        else{
            strncpy(buffer, td->rf->buffer, BUFFER_SIZE);
            strncpy(file, td->rf->pathfile, PATH_MAX);
        }

        // dico al reader di turno che può andare avanti
        td->rf->turn = actual_reader;

        if ((err = pthread_cond_signal(&td->rf->cond[actual_reader])) != 0)
            exit_with_err("pthread_cond_signal", err);

        if ((err = pthread_mutex_unlock(&td->rf->mutex)) != 0)
            exit_with_err("pthread_mutex_unlock", err);

        if (is_valid(td, buffer)) {
            // Inserimento nella struttura dati condivisa con il Writer
            if ((err = pthread_mutex_lock(&td->fw->mutex)) != 0)
                exit_with_err("pthread_mutex_lock", err);

            // fino a quando non tocca al filterer
            while (td->fw->turn != 0)
                if ((err = pthread_cond_wait(&td->fw->cond[0], &td->fw->mutex)) != 0)
                    exit_with_err("pthread_cond_wait", err);

            strncpy(td->fw->buffer, buffer, BUFFER_SIZE);
            strncpy(td->fw->pathfile, file, PATH_MAX);
            
            // a questo punto tocca al writer
            td->fw->turn = 1;

            if ((err = pthread_cond_signal(&td->fw->cond[1])) != 0)
                exit_with_err("pthread_cond_signal", err);

            if ((err = pthread_mutex_unlock(&td->fw->mutex)) != 0)
                exit_with_err("pthread_mutex_unlock", err);
        }
    }

    // appena tutti i reader hanno finito e anche il filterer
    if ((err = pthread_mutex_lock(&td->fw->mutex)) != 0)
        exit_with_err("pthread_mutex_lock", err);

    while (td->fw->turn != 0)
        if ((err = pthread_cond_wait(&td->fw->cond[0], &td->fw->mutex)) != 0)
            exit_with_err("pthread_cond_wait", err);

    td->fw->done = 1;
    td->fw->turn = 1;

    if ((err = pthread_cond_signal(&td->fw->cond[1])) != 0)
        exit_with_err("pthread_cond_signal", err);

    if ((err = pthread_mutex_unlock(&td->fw->mutex)) != 0)
        exit_with_err("pthread_mutex_unlock", err);

    if ((err = pthread_barrier_wait(&td->fw->barrier)) > 0)
        exit_with_err("pthread_barrier_wait", err);
    
    pthread_exit(NULL);
}

void *writer(void *args){
    int err;
    thread_data *td = (thread_data *)args;

    while(1){
        if ((err = pthread_mutex_lock(&td->fw->mutex)) != 0)
            exit_with_err("pthread_mutex_lock", err);

        // fino a quando non tocca al writer
        while (td->fw->turn != 1)
            if ((err = pthread_cond_wait(&td->fw->cond[1], &td->fw->mutex)) != 0)
                exit_with_err("pthread_cond_wait", err);

        // se il filterer ha finito
        if (td->fw->done)
            break;

        printf("\33[1;33m%s\33[0m: %s\n", td->fw->pathfile, td->fw->buffer);

        // può continuare il filterer
        td->fw->turn = 0;

        if ((err = pthread_cond_signal(&td->fw->cond[0])) != 0)
            exit_with_err("pthread_cond_signal", err);

        if ((err = pthread_mutex_unlock(&td->fw->mutex)) != 0)
            exit_with_err("pthread_mutex_unlock", err);
    }

    if ((err = pthread_barrier_wait(&td->fw->barrier)) > 0)
        exit_with_err("pthread_barrier_wait", err);
    
    pthread_exit(NULL);
}

int main(int argc, char **argv){
    if(argc < 3){
        printf("Usage: %s [-v] [-i] [word] <file-1> [file-2] [file-3] [...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int err, _from = 1;
    char *word;
    bool iFlag = 0, vFlag = 0;

    if(!strcmp(argv[1], "-v") || (argc > 2 && !strcmp(argv[2], "-v"))){
        vFlag = 1;
        _from++;
    }

    if(!strcmp(argv[1], "-i") || (argc > 2 && !strcmp(argv[2], "-i"))){
        iFlag = 1;
        _from++;
    }

    thread_data td[argc - _from + 1];
    shared_rf *rf = init_shared_rf(argc - _from - 1);
    shared_fw *fw = init_shared_fw();

    int index = 0;

    // Reader init
    for(int i=_from + 1; i<argc; i++){
        td[index].filepath = argv[i];
        td[index].rf = rf;
        td[index].thread_n = index+1;

        if((err = pthread_create(&td[index].tid, NULL, reader, &td[index])) != 0)
            exit_with_err("pthread_create", err);
        index++;
    }

    // sia per Filterer che per Writer il filepath viene passato durante l'esecuzione
    // Filterer init
    td[index].fw = fw;
    td[index].rf = rf;
    td[index].iFlag = iFlag;
    td[index].vFlag = vFlag;
    td[index].thread_n = 0;
    td[index].word = argv[_from];

    if((err = pthread_create(&td[index].tid, NULL, filterer, &td[index])) != 0)
        exit_with_err("pthread_create", err);
    index++;

    // Writer init
    td[index].fw = fw;
    if((err = pthread_create(&td[index].tid, NULL, writer, &td[index])) != 0)
        exit_with_err("pthread_create", err);
    
    // detach
    for(int i=0; i <= index; i++){
        if((err = pthread_detach(td[i].tid)) != 0)
        exit_with_err("pthread_detach", err);
    }

    if ((err = pthread_barrier_wait(&fw->barrier)) > 0)
        exit_with_err("pthread_barrier_wait", err);

    destroy_shared_rf(rf);
    destroy_shared_fw(fw);
}