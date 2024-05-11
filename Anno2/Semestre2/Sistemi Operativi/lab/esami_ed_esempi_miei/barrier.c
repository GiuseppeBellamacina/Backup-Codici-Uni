/* Le barriere in C sono un meccanismo di sincronizzazione che permette a più thread di attendere fino a quando tutti i thread non raggiungono un certo punto nel loro flusso di esecuzione. Una volta che tutti i thread hanno raggiunto la barriera, tutti possono procedere. Le funzioni principali per la gestione delle barriere nella libreria pthread sono:

1. `int pthread_barrier_init(pthread_barrier_t *restrict barrier, const pthread_barrierattr_t *restrict attr, unsigned count);`
   Questa funzione inizializza la barriera puntata da `barrier`. Il parametro `count` specifica il numero di thread che devono chiamare `pthread_barrier_wait` prima che tutti i thread possano procedere. L'attributo `attr` può essere utilizzato per personalizzare il comportamento della barriera. Se `attr` è `NULL`, viene utilizzata una barriera con attributi di default.

2. `int pthread_barrier_destroy(pthread_barrier_t *barrier);`
   Questa funzione distrugge una barriera, liberando le risorse ad essa associate. La barriera non deve essere utilizzata dopo essere stata distrutta.

3. `int pthread_barrier_wait(pthread_barrier_t *barrier);`
   Questa funzione blocca il thread chiamante sulla barriera specificata. Quando il numero di thread che hanno chiamato questa funzione raggiunge il conteggio specificato nella chiamata a `pthread_barrier_init`, tutti i thread possono procedere.

Ecco un esempio di come queste funzioni potrebbero essere utilizzate: */

#include <pthread.h>
#include <stdio.h>

pthread_barrier_t barrier;

void* worker(void* id) {
    printf("Thread %d: Waiting at the barrier...\n", id);
    pthread_barrier_wait(&barrier);
    printf("Thread %d: Proceeding!\n", id);
    return NULL;
}

int main() {
    pthread_barrier_init(&barrier, NULL, 3);

    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, worker, (void*)1);
    pthread_create(&thread2, NULL, worker, (void*)2);

    printf("Main thread: Waiting at the barrier...\n");
    pthread_barrier_wait(&barrier);
    printf("Main thread: Proceeding!\n");

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_barrier_destroy(&barrier);

    return 0;
}

/*
    In questo esempio, due thread di lavoro e il thread principale attendono a una barriera. Solo quando tutti e tre i thread hanno raggiunto la barriera, tutti possono procedere.
*/