#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int sockfd, n;
struct sockaddr_in remote_addr;
socklen_t len = sizeof(struct sockaddr_in);
char user[100], password[100], ans[100];
char ip[] = "127.0.0.1";
char port[] = "";

void login(){
    printf("Inserisci nome utente: ");
    scanf("%s", user);
    printf("Inserisci a to' password: ");
    scanf("%s", password);

    sendto(sockfd, user, strlen(user)+1, 0, (struct sockaddr *) &remote_addr, len);
    sendto(sockfd, password, strlen(password)+1, 0, (struct sockaddr *) &remote_addr, len);
    n = recvfrom(sockfd, ans, 99, 0, (struct sockaddr *) &remote_addr, &len);
    ans[n] = 0;
    printf("%s\n", ans);
}

void registrazione(){
    printf("Inserisci nome utente: ");
    scanf("%s", user);
    printf("Crea una password: ");
    scanf("%s", password);

    sendto(sockfd, user, strlen(user)+1, 0, (struct sockaddr *) &remote_addr, len);
    sendto(sockfd, password, strlen(password)+1, 0, (struct sockaddr *) &remote_addr, len);
    n = recvfrom(sockfd, ans, 99, 0, (struct sockaddr *) &remote_addr, &len);
    ans[n] = 0;
    printf("%s\n", ans);
}

void elimina(){
    printf("Effettuare il login per eliminare l'account\n");
    login();
    if(strcmp(ans,"Login fallito") == 0){
        printf("Non puoi eliminare un account che non esiste\n");
        system("sleep 5");
        seleziona();
    }
    else{
        char conferma[100];
        printf("Sei sicuro di voler eliminare l'account? (s/n)\n");
        scanf("%s", conferma);
        sendto(sockfd, conferma, 99, 0, (struct sockaddr *) &remote_addr, len);
        if(strcmp(conferma, "s") == 0){
            n = recvfrom(sockfd, ans, 99, 0, (struct sockaddr *) &remote_addr, &len);
            ans[n] = 0;
            printf("%s\n", ans);
        } else return;
    }
}

void seleziona(){
    system("clear");
    printf("Cosa vuoi fare?\n");
    char scelta[100];
    printf("1. Login\n2. Registrazione\n3. Elimina account\n4. Esci\n");
    scanf("%s", scelta);
    sendto(sockfd, scelta, 99, 0, (struct sockaddr *) &remote_addr, len);

    if(strcmp(scelta, "1") == 0) login();
    else if(strcmp(scelta, "2") == 0) registrazione();
    else if(strcmp(scelta, "3") == 0) elimina();
    else if(strcmp(scelta, "4") == 0){
        close(sockfd);
        exit(0);
    }
    else{
        printf("Scelta non valida\n");
        system("sleep 5");
        seleziona();
    }
    system("sleep 5");
}

int main(int argc, char **argv){
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0){
        perror("Errore nella creazione del socket");
        return -1;
    }

    memset(&remote_addr, 0, len);
    remote_addr.sin_family = AF_INET;
    remote_addr.sin_port = htons(atoi(port));
    inet_pton(AF_INET, ip, &remote_addr.sin_addr);

    while(1) seleziona();
}

