#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int sockfd, n, n1, n2;
struct sockaddr_in local_addr, remote_addr;
socklen_t len = sizeof(struct sockaddr_in);
FILE *file;
char user[100], password[100], ans[100];
char port[] = "8000";

void login(){
    n1 = recvfrom(sockfd, user, 99, 0, (struct sockaddr *) &remote_addr, &len);
    n2 = recvfrom(sockfd, password, 99, 0, (struct sockaddr *) &remote_addr, &len);

    user[n1] = 0;
    password[n2] = 0;
    int flag = 0;
    if ((file = fopen("users.txt", "r")) == NULL){
        printf("Errore nell'apertura del file");
        exit(-1);
    }
    char us[100];
    char pa[100];
    while(!feof(file)){
        fscanf(file,"%s",us);
        fscanf(file, "%s", pa);
        if((strcmp(user,us) == 0) && (strcmp(password,pa) == 0)) flag = 1;
    }
    fclose(file);

    if(flag){
        strcpy(ans, "Login effettuato correttamente");
        sendto(sockfd, ans, strlen(ans)+1, 0, (struct sockaddr *) &remote_addr, len);
    }
    else{
        strcpy(ans, "Login fallito");
        sendto(sockfd, ans, strlen(ans)+1, 0, (struct sockaddr *) &remote_addr, len);
    }
}

void registrazione(){
    n1 = recvfrom(sockfd, user, 99, 0, (struct sockaddr *) &remote_addr, &len);
    n2 = recvfrom(sockfd, password, 99, 0, (struct sockaddr *) &remote_addr, &len);

    user[n1] = 0;
    password[n2] = 0;
    if ((file = fopen("users.txt", "a")) == NULL){
        printf("Errore nell'apertura del file");
        exit(-1);
    }
    fprintf(file, "%s ", user);
    fprintf(file, "%s\n", password);
    sendto(sockfd, "Registrazione effettuata correttamente", 40, 0, (struct sockaddr *) &remote_addr, len);
    fclose(file);
}

void elimina(){
    login();
    n = recvfrom(sockfd, ans, 99, 0, (struct sockaddr *) &remote_addr, &len);
    ans[n] = 0;
    if(strcmp(ans, "n") == 0) return;
    else {
        FILE *tmp;
        if ((tmp = fopen("tmp.txt", "w")) == NULL){
            printf("Errore nell'apertura del file tmp");
            exit(-1);
        }
        if ((file = fopen("users.txt", "r")) == NULL){
            printf("Errore nell'apertura del file");
            exit(-1);
        }
        char us[100];
        char pa[100];
        while(!feof(file)){
            fscanf(file,"%s",us);
            fscanf(file, "%s", pa);
            if((strcmp(user,us) == 0) && (strcmp(password,pa) == 0)) continue;
            if(feof(file)) break;
            fprintf(tmp, "%s ", us);
            fprintf(tmp, "%s\n", pa);
        }
        fclose(file);
        fclose(tmp);
        remove("users.txt");
        rename("tmp.txt", "users.txt");
    }
    strcpy(ans, "Eliminazione effettuata correttamente");
    sendto(sockfd, ans, strlen(ans)+1, 0, (struct sockaddr *) &remote_addr, len);
}

void seleziona(){
    n = recvfrom(sockfd, ans, 99, 0, (struct sockaddr *) &remote_addr, &len);
    ans[n] = 0;
    printf("%s\n", ans);
    if(strcmp(ans, "1") == 0) login();
    else if(strcmp(ans, "2") == 0) registrazione();
    else if(strcmp(ans, "3") == 0) elimina();
    else return;
}

int main(int argc, char **argv){
    system("clear");
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0){
        perror("Errore nella creazione del socket");
        return -1;
    }

    memset(&local_addr, 0, len);
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(atoi(port));

    if(bind(sockfd, (struct sockaddr *) &local_addr, len) < 0){
        perror("Errore nella bind");
        return -1;
    }

    while(1) seleziona();
}

