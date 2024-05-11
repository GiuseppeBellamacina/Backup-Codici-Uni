#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>

#define MAX_COUNT 10000

sem_t sem_inc, sem_dec;
int count = 0;

void* incrementer(void* arg) {
    for (int i = 0; i < MAX_COUNT; ++i) {
        sem_wait(&sem_inc);
        ++count;
        printf("Incremented, count = %d\n", count);
        sem_post(&sem_dec);
    }
    return NULL;
}

void* decrementer(void* arg) {
    for (int i = 0; i < MAX_COUNT; ++i) {
        sem_wait(&sem_dec);
        ++count;
        printf("Decremented, count = %d\n", count);
        sem_post(&sem_inc);
    }
    return NULL;
}

int main() {
    sem_init(&sem_inc, 0, 1);
    sem_init(&sem_dec, 0, 0);

    pthread_t inc_thread, dec_thread;
    pthread_create(&inc_thread, NULL, incrementer, NULL);
    pthread_create(&dec_thread, NULL, decrementer, NULL);

    pthread_join(inc_thread, NULL);
    pthread_join(dec_thread, NULL);

    sem_destroy(&sem_inc);
    sem_destroy(&sem_dec);

    return 0;
}
