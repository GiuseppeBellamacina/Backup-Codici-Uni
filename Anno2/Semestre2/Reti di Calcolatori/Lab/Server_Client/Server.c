#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char **argv){
    int sockfd, n;
    struct sockaddr_in local_addr, remote_addr;
    socklen_t len = sizeof(struct sockaddr_in);
    char buffer[100];

    if (argc < 2){
        perror("Errore! Inserisci le informazioni corrette");
        return -1;
    }

    sockfd = socket(AF_INET, SOCK_DGRAM, 0); // Creazione del socket
    if(sockfd < 0){
        perror("Errore nella creazione del socket");
        return -1;
    }

    memset(&local_addr, 0, len); // Pulizia della struttura
    local_addr.sin_family = AF_INET; // Famiglia di protocolli
    local_addr.sin_port = htons(atoi(argv[1])); // Porta del server

    if(bind(sockfd, (struct sockaddr *) &local_addr, len) < 0){
        perror("Errore nella bind");
        return -1;
    }

    n = recvfrom(sockfd, buffer, 99, 0, (struct sockaddr *) &remote_addr, &len); // Ricezione del messaggio, metti 99 che sizeof(buffer) dà problemi
    buffer[n] = 0; // Terminatore di stringa
    printf("Messaggio: %s, IP %s, Port %d", buffer, inet_ntoa(remote_addr.sin_addr), ntohs(remote_addr.sin_port));


    close(sockfd); // Chiusura del socket
    return 0;


    /*
    socket();
    bind();
    recvfrom();
    close();
    */
}