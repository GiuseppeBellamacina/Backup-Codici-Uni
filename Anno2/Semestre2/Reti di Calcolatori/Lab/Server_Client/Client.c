#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char **argv){
    int sockfd; // socket descriptor
    struct sockaddr_in remote_addr; // server address
    socklen_t len = sizeof(struct sockaddr_in); // length of address
    char buffer[100];

    if(argc != 3){
        printf("Errore! Inserisci IP e porta del server\n");
        return -1;
    }

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        perror("Errore nella creazione del socket");
        return -1;
    }

    memset(&remote_addr, 0, len);
    remote_addr.sin_family = AF_INET;
    remote_addr.sin_port = htons(atoi(argv[2]));
    inet_pton(AF_INET, argv[1], &remote_addr.sin_addr);

    printf("Inserisci il messaggio da inviare: ");
    scanf("%s", buffer);

    sendto(sockfd, buffer, strlen(buffer)+1, 0, (struct sockaddr *) &remote_addr, len);
    close(sockfd);
    return 0;
}