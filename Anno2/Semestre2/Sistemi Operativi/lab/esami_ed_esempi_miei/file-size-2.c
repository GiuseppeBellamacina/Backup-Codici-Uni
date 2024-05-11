#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

typedef struct node {
    long size;
    struct node* next;
} node;

node* head = NULL;
int dir_threads_active = 0;

void push(long size) {
    node* new_node = (node*)malloc(sizeof(node));
    new_node->size = size;
    new_node->next = head;
    head = new_node;
}

long pop_min_max() {
    node *prev_min = NULL, *prev_max = NULL;
    node *min = head, *max = head, *tmp = head;

    while(tmp->next) {
        if(tmp->next->size < min->size) {
            prev_min = tmp;
            min = tmp->next;
        }
        if(tmp->next->size > max->size) {
            prev_max = tmp;
            max = tmp->next;
        }
        tmp = tmp->next;
    }

    // Handle case when min and max are the only nodes in the list.
    if(min == max) {
        head = NULL;
    } else {
        if(prev_min) prev_min->next = min->next;
        else head = min->next;

        // Need to update prev_max in case min was removed and it was before max
        if(min == prev_max) prev_max = prev_min;

        if(prev_max) prev_max->next = max->next;
        else head = max->next;
    }

    long sum = min->size + max->size;
    free(min);
    if(min != max) free(max);
    
    return sum;
}


void* dir_thread(void* arg) {
    char* dir_name = (char*)arg;
    DIR* dir;
    struct dirent* ent;
    struct stat statbuf;
    char* path;

    printf("[DIR] scansione della cartella '%s'...\n", dir_name);
    dir = opendir(dir_name);
    while((ent = readdir(dir))) {
        path = malloc(strlen(dir_name) + strlen(ent->d_name) + 2);
        strcpy(path, dir_name);
        strcat(path, "/");
        strcat(path, ent->d_name);

        if(stat(path, &statbuf) == 0 && S_ISREG(statbuf.st_mode)) {
            printf("[DIR] trovato il file '%s' di %ld byte\n", ent->d_name, statbuf.st_size);
            pthread_mutex_lock(&mutex);
            push(statbuf.st_size);
            pthread_cond_broadcast(&cond);
            pthread_mutex_unlock(&mutex);
        }
        free(path);
    }
    closedir(dir);
    pthread_mutex_lock(&mutex);
    dir_threads_active--;
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* add_thread(void* arg) {
    long sum;
    while(1) {
        pthread_mutex_lock(&mutex);
        while(!head || !head->next) {
            if(dir_threads_active == 0 && (!head || !head->next)) {
                pthread_mutex_unlock(&mutex);
                return NULL;
            }
            pthread_cond_wait(&cond, &mutex);
        }
        sum = pop_min_max();
        printf("[ADD] il minimo e il massimo sono stati sostituiti da %ld\n", sum);
        push(sum);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(int argc, char** argv) {
    pthread_t* dir_thread_ids = malloc((argc-1) * sizeof(pthread_t));
    pthread_t add_thread_id1, add_thread_id2;
    int i;

    dir_threads_active = argc-1;
    for(i = 1; i < argc; i++) {
        pthread_create(&dir_thread_ids[i-1], NULL, dir_thread, argv[i]);
    }

    pthread_create(&add_thread_id1, NULL, add_thread, NULL);
    pthread_create(&add_thread_id2, NULL, add_thread, NULL);

    for(i = 1; i < argc; i++) {
        pthread_join(dir_thread_ids[i-1], NULL);
    }

    pthread_join(add_thread_id1, NULL);
    pthread_join(add_thread_id2, NULL);

    printf("[MAIN] i thread secondari hanno terminato e il totale finale è di %ld byte\n", head->size);

    free(head);
    free(dir_thread_ids);
    return 0;
}
