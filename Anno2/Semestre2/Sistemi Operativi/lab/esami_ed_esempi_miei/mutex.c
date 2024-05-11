/*
    In C, i mutex (o mutui esclusivi) sono utilizzati per proteggere le sezioni di codice che non possono essere eseguite contemporaneamente da più thread. Le funzioni di base per la gestione dei mutex in C sono fornite dalla libreria pthread, e includono:

1. `int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);`
   Questa funzione inizializza il mutex puntato da `mutex`. L'attributo `attr` può essere utilizzato per personalizzare il comportamento del mutex. Se `attr` è `NULL`, viene utilizzato un mutex con attributi di default.

2. `int pthread_mutex_destroy(pthread_mutex_t *mutex);`
   Questa funzione distrugge un mutex, liberando le risorse ad esso associate. Il mutex non deve essere utilizzato dopo essere stato distrutto.

3. `int pthread_mutex_lock(pthread_mutex_t *mutex);`
   Questa funzione blocca il mutex specificato. Se il mutex è già bloccato, il thread chiamante sarà bloccato fino a quando il mutex non sarà sbloccato.

4. `int pthread_mutex_unlock(pthread_mutex_t *mutex);`
   Questa funzione sblocca il mutex specificato. Se altri thread sono bloccati sul mutex, uno di essi sarà sbloccato e potrà proseguire.

5. `int pthread_mutex_trylock(pthread_mutex_t *mutex);`
   Questa funzione cerca di bloccare il mutex specificato. Se il mutex è già bloccato, la funzione ritorna immediatamente con un codice di errore invece di bloccarsi.

    Ecco un esempio di come queste funzioni potrebbero essere utilizzate: */

#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mutex;
int counter = 0;

void* increment(void* unused) {
    for (int i = 0; i < 1000000; ++i) {
        pthread_mutex_lock(&mutex);
        ++counter;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_mutex_init(&mutex, NULL);

    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, increment, NULL);
    pthread_create(&thread2, NULL, increment, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Counter: %d\n", counter);

    pthread_mutex_destroy(&mutex);

    return 0;
}

/*
    In questo esempio, due thread incrementano una variabile condivisa `counter` un milione di volte ciascuno. L'accesso a `counter` è protetto da un mutex, il che assicura che solo un thread alla volta possa incrementare il contatore. Senza il mutex, i due thread potrebbero cercare di incrementare il contatore contemporaneamente, il che potrebbe portare a un comportamento indeterminato.
*/