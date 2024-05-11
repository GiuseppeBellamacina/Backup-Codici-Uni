#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER 1
#define CLIENT 0

int sockfd, n;
struct sockaddr_in local_addr, remote_addr;
socklen_t len = sizeof(struct sockaddr_in);
FILE *file;
char dest_ip[20] = "";
char my_port[20] = "8000"; // porta base del server
char msg_port[20] = "8001"; // porta dei messaggi
char dest_port[20] = "";

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

struct FileReader{
    char username[50];
    char password[50];
    char port[20];
    int32_t token;
    char ip[20];
};

struct MessageS{
    char msg[100];
    char mittente[50];
};

struct MessageC{
    char msg[100];
    int32_t token;
};

void create_socket(int type, char *port){ // 0 = client, 1 = server
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        printf("Errore nell'apertura del socket\n");
        exit(1);
    }
    if(type){ // Server
        memset(&local_addr, 0, sizeof(local_addr));
        local_addr.sin_family = AF_INET;
        local_addr.sin_port = htons(atoi(port));
        if(bind(sockfd, (struct sockaddr *) &local_addr, sizeof(local_addr)) < 0){
            printf("Errore nel binding di: %s\n", port);
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
    struct Registrazione reg;
    struct RegResponse res;
    printf("Registrazione in corso...\n");
    recvfrom(sockfd, &reg, sizeof(reg), 0, (struct sockaddr *) &remote_addr, &len);
    
    if((file = fopen("users.txt", "a+")) == NULL){
        printf("Errore nell'apertura del file\n");
        exit(1);
    }

    // Controllo se l'username è già presente nel file
    char line[100];
    while(fgets(line, sizeof(line), file)){
        char *token = strtok(line, " ");
        char tmp[50];
        if(token != NULL) strcpy(tmp, token);
        if(strcmp(tmp, reg.username) == 0){
            strcpy(res.esito, "Username già in uso");
            res.token = -1;
            sendto(sockfd, &res, sizeof(res), 0, (struct sockaddr *) &remote_addr, len);
            exit(1);
        }
    }

    // Se l'username non è presente nel file, lo aggiungo
    srand(time(NULL));
    res.token = rand(); // Genero un token casuale
    fprintf(file, "%s %s %s %d %s\n", reg.username, reg.password, reg.port, res.token, inet_ntoa(remote_addr.sin_addr));
    fclose(file);
    strcpy(res.esito, "Registrazione completata");
    sendto(sockfd, &res, sizeof(res), 0, (struct sockaddr *) &remote_addr, len);
}

void login(){
    struct Login log;
    struct FileReader fr;
    char ans[100];
    recvfrom(sockfd, &log, sizeof(log), 0, (struct sockaddr *) &remote_addr, &len);

    if((file = fopen("users.txt", "r")) == NULL){
        printf("Errore nell'apertura del file\n");
        exit(1);
    }
    char line[100];
    while(fgets(line, sizeof(line), file)){
        char *tmp = strtok(line, " ");
        strcpy(fr.username, tmp);
        tmp = strtok(NULL, " ");
        strcpy(fr.password, tmp);
        tmp = strtok(NULL, " ");
        strcpy(fr.port, tmp);
        tmp = strtok(NULL, " ");
        fr.token = atoi(tmp);
        tmp = strtok(NULL, "\n");
        strcpy(fr.ip, tmp);

        if(fr.token == log.token){
            printf("Login effettuato da \33[1;33m%s\33[0m\n", fr.ip);
            strcpy(ans, "Login effettuato");
            sendto(sockfd, ans, strlen(ans)+1, 0, (struct sockaddr *) &remote_addr, len);
        }
    }
    fclose(file);
    strcpy(ans, "Login fallito");
    sendto(sockfd, ans, strlen(ans)+1, 0, (struct sockaddr *) &remote_addr, len);
}

void seleziona(){
    strcpy(my_port, "8000");
    create_socket(SERVER, my_port);
    printf("In attesa di richieste...\n");
    int scelta;
    recvfrom(sockfd, &scelta, sizeof(scelta), 0, (struct sockaddr *) &remote_addr, &len);
    switch(scelta){
        case 1:
            registrazione();
            break;
        case 2:
            login();
            break;
    }
    close(sockfd);
}

void send_messages(){
    struct MessageC msgC;
    struct MessageS msgS;
    struct FileReader fr;

    recvfrom(sockfd, &msgC, sizeof(msgC), 0, (struct sockaddr *) &remote_addr, &len);
    if(strcmp(msgC.msg, "exit\n") == 0){
        printf("Logout di \33[1;33m%s\33[0m\n", inet_ntoa(remote_addr.sin_addr));
        strcpy(msgS.msg, "EXIT");
        strcpy(msgS.mittente, "Server");
        sendto(sockfd, &msgS, sizeof(msgS), 0, (struct sockaddr *) &remote_addr, len);
        close(sockfd);
        return;
    }
    close(sockfd);
    if((file = fopen("users.txt", "r")) == NULL){
        printf("Errore nell'apertura del file\n");
        exit(1);
    }
    char line[100];
    while(fgets(line, sizeof(line), file)){
        char *tmp = strtok(line, " ");
        strcpy(fr.username, tmp);
        tmp = strtok(NULL, " ");
        strcpy(fr.password, tmp);
        tmp = strtok(NULL, " ");
        strcpy(fr.port, tmp);
        tmp = strtok(NULL, " ");
        fr.token = atoi(tmp);
        tmp = strtok(NULL, "\n");
        strcpy(fr.ip, tmp);
    
        if(fr.token == msgC.token){
            strcpy(msgS.msg, msgC.msg);
            strcpy(msgS.mittente, fr.username);
            break;
        }
    }
    fclose(file);
    
    if((file = fopen("users.txt", "r")) == NULL){
        printf("Errore nell'apertura del file\n");
        exit(1);
    }
    while(fgets(line, sizeof(line), file)){
        char *tmp = strtok(line, " ");
        strcpy(fr.username, tmp);
        tmp = strtok(NULL, " ");
        strcpy(fr.password, tmp);
        tmp = strtok(NULL, " ");
        strcpy(fr.port, tmp);
        tmp = strtok(NULL, " ");
        fr.token = atoi(tmp);
        tmp = strtok(NULL, "\n");
        strcpy(fr.ip, tmp);
        if(strcmp(inet_ntoa(remote_addr.sin_addr), fr.ip) != 0){
            strcpy(dest_ip, fr.ip);
            create_socket(CLIENT, fr.port);
            sendto(sockfd, &msgS, sizeof(msgS), 0, (struct sockaddr *) &remote_addr, len);
            close(sockfd);
        }
    }
    fclose(file);
}

int main(int argc, char **argv){
    int pid = fork();
    if(pid == 0){
        while(1) seleziona();
    }
    else{
        while(1){
            // porta per i messaggi del server
            create_socket(SERVER, msg_port);
            send_messages();
        }
    }
    return 0;
}