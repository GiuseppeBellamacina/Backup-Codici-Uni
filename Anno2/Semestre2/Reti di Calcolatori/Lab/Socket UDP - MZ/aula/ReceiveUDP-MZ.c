#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>

int main(int argc, char **argv){

    int sockfd, n;
    struct sockaddr_in local_addr, dest_addr;
    socklen_t len = sizeof(struct sockaddr_in);

    char buffer[100];

    if(argc < 2){
        printf("Errore! Inserisci la porta.\n");
        return 0;
    }

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        printf("Errore nell'apertura di socket\n");
        return -1;
    }

    memset(&local_addr, 0, len);
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(atoi(argv[1]));

    if(bind(sockfd, (struct sockaddr *)&local_addr, len) < 0){
        printf("Errore! Inserisci un numero di porta valido\n");
        return -1;
    }

    for(;;){
        n = recvfrom(sockfd, buffer, 99, 0,
                    (struct sockaddr *)&dest_addr, &len);
        buffer[n] = 0;

        printf("Messaggio %s, IP %s, Port %d\n",
                        buffer,
                        inet_ntoa(dest_addr.sin_addr),
                        ntohs(dest_addr.sin_port));

        sendto(sockfd, buffer, strlen(buffer), 0, 
                                (struct sockaddr *)&dest_addr, len);
    }
    close(sockfd);

    return 0;
}