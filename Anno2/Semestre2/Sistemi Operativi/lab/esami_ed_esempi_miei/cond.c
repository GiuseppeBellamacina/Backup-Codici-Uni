/*
    Le variabili di condizione (o "cond") in C sono utilizzate per far sì che un thread attenda finché una certa condizione non si verifica. Le funzioni che gestiscono le variabili di condizione sono anch'esse fornite dalla libreria pthread. Ecco le funzioni principali:

1. `int pthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr);`
   Questa funzione inizializza la variabile di condizione puntata da `cond`. L'attributo `attr` può essere utilizzato per personalizzare il comportamento della variabile di condizione. Se `attr` è `NULL`, viene utilizzata una variabile di condizione con attributi di default.

2. `int pthread_cond_destroy(pthread_cond_t *cond);`
   Questa funzione distrugge una variabile di condizione, liberando le risorse ad essa associate. La variabile di condizione non deve essere utilizzata dopo essere stata distrutta.

3. `int pthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex);`
   Questa funzione blocca il thread chiamante sulla variabile di condizione `cond`. Prima di chiamare questa funzione, il thread deve avere bloccato il mutex `mutex`. Quando `pthread_cond_wait` è chiamato, il mutex viene automaticamente sbloccato, consentendo ad altri thread di bloccarlo. Quando il thread viene risvegliato (ad esempio a causa di una chiamata a `pthread_cond_signal` o `pthread_cond_broadcast`), il mutex viene nuovamente bloccato.

4. `int pthread_cond_signal(pthread_cond_t *cond);`
   Questa funzione risveglia un thread che sta aspettando sulla variabile di condizione `cond`. Se più thread stanno aspettando, ne viene risvegliato solo uno (il thread specifico che viene risvegliato può dipendere dal sistema operativo e dalla libreria C).

5. `int pthread_cond_broadcast(pthread_cond_t *cond);`
   Questa funzione risveglia tutti i thread che stanno aspettando sulla variabile di condizione `cond`.

6. `int pthread_cond_timedwait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex, const struct timespec *restrict abstime);`
   Questa funzione è simile a `pthread_cond_wait`, ma ritorna se la condizione non si verifica entro un certo periodo di tempo. L'argomento `abstime` specifica il tempo massimo di attesa.

Le variabili di condizione sono tipicamente utilizzate insieme ai mutex per proteggere l'accesso a una risorsa condivisa e per attendere finché una certa condizione non si verifica.
*/

// produttore consumatore con variabili di condizione
#include <pthread.h>
#include <stdio.h>

#define MAX 100

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int buffer[MAX];
int count = 0;

void* producer(void* arg) {
    for (int i = 0; i < MAX; ++i) {
        pthread_mutex_lock(&mutex);
        buffer[count] = i;
        ++count;
        printf("Produced: %d\n", i);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* consumer(void* arg) {
    int i;
    for (i = 0; i < MAX; ++i) {
        pthread_mutex_lock(&mutex);
        while (count == 0)
            pthread_cond_wait(&cond, &mutex);
        --count;
        printf("Consumed: %d\n", buffer[count]);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    return 0;
}
