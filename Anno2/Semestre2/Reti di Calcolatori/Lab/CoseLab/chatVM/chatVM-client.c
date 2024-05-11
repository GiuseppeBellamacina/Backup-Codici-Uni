#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER 1
#define CLIENT 0

int languageNumber = 0; // 0 = C, 1 = C++, 2 = Java, 3 = Python, 4 = R, 5 = Matlab
char languageName[10] = "C"; // C, C++, Java, Python, R, Matlab

int sockfd, n;
struct sockaddr_in local_addr, remote_addr;
socklen_t len = sizeof(struct sockaddr_in);
char dest_ip[20] = "192.168.56.101"; // IP of the server
char my_port[20] = "7000";
char dest_port[20] = "8000";

struct Request{
    int n;
    int languageNumber;
    char languageName[10];
    char message[20];
};


void create_socket(int type){ // 0 = client, 1 = server
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        printf("\33[1;31mErrore nella creazione della socket\n\33[0m");
        exit(1);
    }
    if(type){ // Server/Receiver
        memset(&local_addr, 0, sizeof(local_addr));
        local_addr.sin_family = AF_INET;
        local_addr.sin_port = htons(atoi(my_port));
        if(bind(sockfd, (struct sockaddr *) &local_addr, sizeof(local_addr)) < 0){
            printf("\33[1;31mErrore nel binding di %s\n\33[0m", my_port);
            exit(1);
        }
    }
    else{ // Client/Sender
        memset(&remote_addr, 0, sizeof(remote_addr));
        remote_addr.sin_family = AF_INET;
        remote_addr.sin_port = htons(atoi(dest_port));
        inet_pton(AF_INET, dest_ip, &remote_addr.sin_addr);
    }
}

void send_request(){
    struct Request req;;
    req.languageNumber = languageNumber;
    strcpy(req.languageName, languageName);
    req.n = -1; // invalid value
    while(req.n < 1 || req.n > 6){
        printf("Inserisci un valore n tra 1 e 6: ");
        scanf("%d", &req.n);
    }
    printf("Inserisci un messaggio: ");
    scanf("%s", req.message);
    sendto(sockfd, &req, sizeof(req), 0, (struct sockaddr *) &remote_addr, len);
}

void recv_reply(){
    struct Request req;
    recvfrom(sockfd, &req, sizeof(req), 0, (struct sockaddr *) &remote_addr, &len);
    system("clear");
    printf("Il messaggio di \33[1;34mVMClient %s\33[0m è: %s\n", req.languageName, req.message);
    sleep(2);
    system("clear");
    printf("Inserisci un valore n tra 1 e 6: ");
    fflush(stdout); // flush stdout buffer
}

int main(int argc, char **argv){
    system("clear");
    int pid = fork();
    if(pid == 0){ // child
        create_socket(SERVER);
        while(1) recv_reply();
        close(sockfd);
    }
    else{ // parent
        create_socket(CLIENT);
        while(1) send_request();
        close(sockfd);
    }
    return 0;
}