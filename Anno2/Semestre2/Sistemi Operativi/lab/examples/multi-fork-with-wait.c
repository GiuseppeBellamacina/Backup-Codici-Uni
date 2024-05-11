/**
 * il padre crea 3 figli e ne attende la terminazione raccogliendo le
 * informazioni deducibili
 */

#include "lib-misc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define NUM_CHILDREN 3
#define MAX_PAUSE 8
#define MAX_EXIT_CODE 10

// generica funzione che rappresenta il corpo del figlio
void child_function(int id) {
    // inizializzazione del generatore di numeri pseudo-casuali con un seed
    // distinti
    // NB: probabilmente time(NULL) è uguale su tutti i figli
    srand(time(NULL) + id*100);

    int pause = rand() % (MAX_PAUSE + 1);
    int exit_code = rand() % (MAX_EXIT_CODE + 1);

    printf("[F%d] figlio attivato con pid %d...\n", id, getpid());

    printf("[F%d] pausa causale di %d secondi...\n", id, pause);
    sleep(pause);

    printf("[F%d] terminazione con exit-code casuale %d\n", id, exit_code);

    exit(exit_code);
}

int main(int argc, char *argv[]) {
    printf("[P] padre attivato con pid %d\n", getpid());

    // creazione dei figli
    for (int i = 1; i <= NUM_CHILDREN; i++) {
        printf("[P] creazione del figlio F%d...\n", i);
        if (fork() == 0)
            child_function(i);
    }

    // attesa della terminazione dei figli
    for (int i = 1; i <= NUM_CHILDREN; i++) {
        printf("[P] attesa terminazione del prossimo figlio...\n");
        int exit_status, pid;
        if ((pid = wait(&exit_status)) <= 0)
            exit_with_sys_err("wait");
        printf("[P] figlio con pid %d terminato con exit-code %d\n", pid,
               WEXITSTATUS(exit_status));
    }

    printf(
        "[P] terminazione di tutti i figli avvenuta: terminazione del padre\n");

    exit(EXIT_SUCCESS);
}
