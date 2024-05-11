/*
 * libreria di servizio ufficiosa per:
 * - fornire utili macro per funzionalità ricorrenti come la gestione
 *   dell'uscita su errore su chiamate di sistema e di libreria
 * - forzatura dell'uso di chiamate POSIX compatibili anche su Linux (dove di
 *   default sono attive diverse estensioni GNU)
 */

#ifndef LIB_OSLAB_MISC_H
#define LIB_OSLAB_MISC_H

#ifdef __linux__

#define _POSIX_C_SOURCE 200809L

#endif

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* esce con un exit code di errore visualizzando un prefisso a scelta `s`
 * seguito dal messaggio di errore standard associato all'attuale codice in
 * `errno` */
#define exit_with_sys_err(s)                                                   \
    do {                                                                       \
        fprintf(stderr, "\33[1;31m%s\33[0m: %s\n", (s), strerror((errno)));                                                           \
        exit(EXIT_FAILURE);                                                    \
    } while (0)

/* esce con un exit code di errore visualizzando un prefisso a scelta `s`
 * seguito dal messaggio di errore standard associato al codice di errore
 * passato (utile per le funzione delle pthread che non usano `errno`) */
#define exit_with_err(s, e)                                                    \
    do {                                                                       \
        fprintf(stderr, "\33[1;31m%s\33[0m: %s\n", (s), strerror((e)));                       \
        exit(EXIT_FAILURE);                                                    \
    } while (0)

/* esce con un exit code di errore visualizzando un messaggio a scelta con le
 * convenzioni del printf */
#define exit_with_err_msg(...)                                                 \
    do {                                                                       \
        fprintf(stderr, "\33[1;31m"__VA_ARGS__"\33[0m");                                          \
        exit(EXIT_FAILURE);                                                    \
    } while (0)

/* PS: il costrutto `do {} while (0)` nella macro serve per forzare il
 * compilatore a trattarlo come una vera e propria funzione (ad esempio
 * obbligando l'uso del punto-e-virgola subito dopo) */

#endif /* LIB_OSLAB_MISC_H */