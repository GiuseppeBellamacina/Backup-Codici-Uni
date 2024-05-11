#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>

#define RED "\33[1;31m"
#define GREEN "\33[1;32m"
#define YELLOW "\33[1;33m"
#define ColRESET "\33[0m"

#define SENDER 1
#define RECEIVER 0

int sockfd, n;
struct sockaddr_in remote_addr, local_addr;
socklen_t len = sizeof(struct sockaddr_in);
int my_port = 7000; // porta di ricezione
char dest_addr[16] = "10.0.4.1"; // indirizzo del server
int dest_port = 8000; // porta del server

void create_socket(int type){
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        printf(RED"Errore nella creazione della socket"ColRESET);
        exit(EXIT_FAILURE);
    }
    if(type){ //SENDER
        memset(&remote_addr, 0, len);
        remote_addr.sin_family = AF_INET;
        remote_addr.sin_port = htons(dest_port);
        inet_pton(AF_INET, dest_addr, &(remote_addr.sin_addr));
    }
    else{ // RECEIVER
        memset(&local_addr, 0, len);
        local_addr.sin_family = AF_INET;
        local_addr.sin_port = htons(my_port);
        if(bind(sockfd, (struct sockaddr *)&local_addr, len) < 0){
            printf(RED"Errore nella bind \n"ColRESET);
            exit(EXIT_FAILURE);
        }
    }
}

void registrazione(){
    system("clear");
    create_socket(SENDER);
    printf("Registrazione al server in corso...\n");
    // invio al server la mia porta di ricezione
    sendto(sockfd, &my_port, sizeof(int), 0, (struct sockaddr *)&remote_addr, len);
    // attendo la risposta del server
    char answer[100];
    recvfrom(sockfd, answer, sizeof(answer)-1, 0, (struct sockaddr *)&remote_addr, &len);
    printf("%s\n", answer);
    close(sockfd);
}

void game(){
    create_socket(RECEIVER);
    printf("In attesa di un avversario...\n");
    // attendo la connessione di un avversario
    while(1){
        char answer[100];
        recvfrom(sockfd, answer, sizeof(answer)-1, 0, (struct sockaddr *)&remote_addr, &len);
        system("clear");
        printf("%s\n", answer);
        // faccio la mia mossa
        Move move;
        while(move != SASSO && move != CARTA && move != FORBICI){
            printf("Sasso, carta o forbici? [s/c/f]");
            scanf("%c", &move);
            getchar(); // rimuovo il carattere \n
        }
        // invio la mia mossa al server
        sendto(sockfd, &move, sizeof(Move), 0, (struct sockaddr *)&remote_addr, len);
        // attendo l'esito del round dal server
        printf("In attesa dell'esito del round...\n");
        recvfrom(sockfd, answer, sizeof(answer)-1, 0, (struct sockaddr *)&remote_addr, &len);
        printf("%s\n", answer);
        if(strcmp(answer, "Hai vinto!") == 0 || strcmp(answer, "Hai perso!") == 0){
            sleep(5);
            break;
        }
    }
    close(sockfd);
}

int main(){
    registrazione();
    return 0;
}