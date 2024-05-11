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
int my_port = 8000; // porta di ricezione

typedef enum{
    SASSO = 's',
    CARTA = 'c',
    FORBICI = 'f'
} Move;

typedef enum{
    GIOCATORE1,
    GIOCATORE2,
    NESSUNO
} Player;

typedef struct{
    int round;
    int lives[2];
    struct sockaddr_in player_addr[2];
    socklen_t addr_len[2];
    int player_ports[2];
    Move moves[2];
    Player winner;
} Round;

Round round;

void create_socket(int type, char* addr, int port){
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        printf(RED"Errore nella creazione della socket"ColRESET);
        exit(EXIT_FAILURE);
    }
    if(type){ //SENDER
        memset(&remote_addr, 0, len);
        remote_addr.sin_family = AF_INET;
        remote_addr.sin_port = htons(port);
        inet_pton(AF_INET, addr, &(remote_addr.sin_addr));
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
    create_socket(RECEIVER, NULL, 0);
    for(int i=0; i<2; i++){
        printf("Registrazione Giocatore %d in corso...\n", i+1);
        int dest_port;
        recvfrom(sockfd, &dest_port, sizeof(int), 0, (struct sockaddr *)&remote_addr, &len);
        round.player_addr[i] = remote_addr;
        round.addr_len[i] = len;
        round.player_ports[i] = dest_port;
        printf(GREEN"Giocatore %d registrato con successo\n"ColRESET, i+1);
        char answer[100] = "Giocatore registrato con successo";
        sendto(sockfd, answer, sizeof(answer)+1, 0, (struct sockaddr *)&remote_addr, len);
    }
    close(sockfd);
}

void init(){
    round.round = 0;
    round.lives[0] = 3;
    round.lives[1] = 3;
}

int main(){
    init();
    registrazione();
    
    return 0;
}