#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>

int main(int argc, char **argv){

    int sockfd, n;
    struct sockaddr_in dest_addr;
    socklen_t len = sizeof(struct sockaddr_in);
    char buffer[100];

    if(argc < 3){
        printf("Errore! Inserisci IP e porta\n");
        return 0;
    }

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0){
        printf("Errore nell'apertura di socket.\n");
        return -1;
    }

    memset(&dest_addr, 0, len);
    dest_addr.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &(dest_addr.sin_addr));
    dest_addr.sin_port = htons(atoi(argv[2]));

    //int n;
    //printf("Inserisci un numero intero\n");
    //scanf("%d", &n);

    //Prima modalità
    /*
    for(int i=0; i<10; i++){
        //sprintf(buffer, "%d", i+n);
        printf("Inserisci la parola numero %d\n", i);
        scanf("%s", &buffer);
        sendto(sockfd, buffer, strlen(buffer), 0, 
                    (struct sockaddr *)&dest_addr, len);

        n = recvfrom(sockfd, buffer, 99, 0, 
                    (struct sockaddr *)&dest_addr, &len);
        buffer[n] = 0;
        printf("Messaggio %s, IP %s, Port %d\n",
                        buffer,
                        inet_ntoa(dest_addr.sin_addr),
                        ntohs(dest_addr.sin_port));
        if(strcmp(buffer, "fine") == 0)
            break;
    }
    */

    while(fgets(buffer, 99, stdin) != NULL){
        
        sendto(sockfd, buffer, strlen(buffer), 0, 
                    (struct sockaddr *)&dest_addr, len);

        n = recvfrom(sockfd, buffer, 99, 0, 
                    (struct sockaddr *)&dest_addr, &len);
        buffer[n] = 0;
        printf("Messaggio %s, IP %s, Port %d\n",
                        buffer,
                        inet_ntoa(dest_addr.sin_addr),
                        ntohs(dest_addr.sin_port));
        if(strcmp(buffer, "fine") == 0)
            break;
    }
    

    close(sockfd);
    return 0;
}