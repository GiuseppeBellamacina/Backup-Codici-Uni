#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

// sistema la roba del fork che mi rompo i coglioni
#define SERVER 1
#define CLIENT 0

// PORCABUTTANA, ogni client ha solo un utente registrato
int sockfd, n;
struct sockaddr_in local_addr, remote_addr;
socklen_t len = sizeof(struct sockaddr_in);
char dest_ip[20] = "192.168.56.101";
char my_port[20] = "";
char msg_port[20] = "8001"; // porta dei messaggi del server
char dest_port[20] = "8000"; // porta base del server;
int32_t TOTK = -1;

struct Registrazione{
    char username[50];
    char password[50];
    char port[20];
};

struct RegResponse{
    char esito[30];
    int32_t token;
};

struct Login{
    int32_t token;
};

struct MessageS{
    char msg[100];
    char mittente[50];
};

struct MessageC{
    char msg[100];
    int32_t token;
};

void create_socket(int type, char* port){ // 0 = client, 1 = server
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        printf("Errore nel binding di: %s\n", port);
        exit(1);
    }
    if(type){ // Server
        memset(&local_addr, 0, sizeof(local_addr));
        local_addr.sin_family = AF_INET;
        local_addr.sin_port = htons(atoi(port));
        if(bind(sockfd, (struct sockaddr *) &local_addr, sizeof(local_addr)) < 0){
            printf("Errore nel binding\n");
            exit(1);
        }
    }
    else{ // Client
        memset(&remote_addr, 0, sizeof(remote_addr));
        remote_addr.sin_family = AF_INET;
        remote_addr.sin_port = htons(atoi(port));
        inet_pton(AF_INET, dest_ip, &remote_addr.sin_addr);
    }
}

void registrazione(){
    system("clear");
    create_socket(CLIENT, dest_port);
    struct Registrazione reg;
    struct RegResponse res;
    printf("Inserisci username: ");
    scanf("%s", reg.username);
    printf("Inserisci password: ");
    scanf("%s", reg.password);
    printf("Inserisci porta: ");
    scanf("%s", reg.port);
    strcpy(my_port, reg.port);
    sendto(sockfd, &reg, sizeof(reg), 0, (struct sockaddr *) &remote_addr, len);
    recvfrom(sockfd, &res, sizeof(res), 0, (struct sockaddr *) &remote_addr, &len);
    printf("%s\n", res.esito);
    if(res.token != -1){
        TOTK = res.token;
        printf("Il tuo token è: %d\n", TOTK);
    }
    close(sockfd);
    sleep(3);
}

void padre(){
    create_socket(SERVER, my_port);
    struct MessageS msg;
    while(1){
        recvfrom(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *) &remote_addr, &len);
        if(strcmp(msg.msg, "EXIT") == 0) return;
        printf("Mittente: %s, Messaggio: %s", msg.mittente, msg.msg);
    }
}

void figlio(){
    // porta messaggi
    create_socket(CLIENT, msg_port);
    struct MessageC msg;
    getchar();
    while(fgets(msg.msg, sizeof(msg.msg), stdin)){
        msg.token = TOTK;
        sendto(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *) &remote_addr, len);
        if(strcmp(msg.msg, "exit\n") == 0){
            return;
        }
    }
}

void login(){
    system("clear");
    create_socket(CLIENT, dest_port);
    struct Login log;
    char ans[100];
    if(TOTK == -1){
        printf("Errore, non sei registrato\n");
        sleep(3);
        return;
    }
    log.token = TOTK;
    sendto(sockfd, &log, sizeof(log), 0, (struct sockaddr *) &remote_addr, len);
    n = recvfrom(sockfd, ans, sizeof(ans)-1, 0, (struct sockaddr *) &remote_addr, &len);
    ans[n] = '\0';
    printf("%s\n", ans);
    close(sockfd);
    int pid;
    if(strcmp(ans, "Login effettuato") == 0){
        printf("Puoi inviare messaggi\n");
        pid = fork();
    }
    else return;
    if(pid == 0){
        figlio();
        close(sockfd);
        exit(EXIT_SUCCESS);
    }
    else{
        padre();
        close(sockfd);
    }
    printf("Logout\n");
    sleep(3);
}

void seleziona(){
    system("clear");
    create_socket(CLIENT, dest_port);
    int scelta;
    printf("1. Registrazione\n2. Login\n");
    scanf("%d", &scelta);
    switch(scelta){
        case 1:
            sendto(sockfd, &scelta, sizeof(scelta), 0, (struct sockaddr *) &remote_addr, len);
            registrazione();
            break;
        case 2:
            sendto(sockfd, &scelta, sizeof(scelta), 0, (struct sockaddr *) &remote_addr, len);
            login();
            break;
        default:
            printf("Scelta non valida\n");
            break;
    }
    close(sockfd);
}

int main(int argc, char **argv){
    while(1) seleziona();
    return 0;
}