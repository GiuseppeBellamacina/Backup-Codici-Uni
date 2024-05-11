#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h> // per SIGTERM
#include <sys/types.h>

int sockfd, n;
struct sockaddr_in local_addr, remote_addr;
socklen_t len = sizeof(struct sockaddr_in);
char ans[100];
char ip[] = "1.1.4.10";
char port[] = "8000";

struct Registrazione{
    char user[30];
    char secret[50];
    char ips[30];
};

struct Login{
    char user[30];
    char ip[30];
};

struct Login loginfo;

// per chiudere i processi del fork
pid_t child;
void terminator(){
    kill(child, SIGTERM);
    kill(getpid(), SIGTERM);
}

void registrazione(){
    system("clear");
    struct Registrazione reg;
    printf("Inserisci nome utente: ");
    scanf("%s", reg.user);
    getchar();
    printf("Dimmi il tuo segreto: ");
    fgets(reg.secret, sizeof(reg.secret), stdin);
    reg.secret[strcspn(reg.secret, "\n")] = '\0';
    printf("Dimmi a chi posso dirlo (separa le macchine con uno spazio): ");
    fgets(reg.ips, sizeof(reg.ips), stdin);
    reg.ips[strcspn(reg.ips, "\n")] = '\0';

    sendto(sockfd, &reg, sizeof(reg), 0, (struct sockaddr *) &remote_addr, len);
    memset(ans, 0, sizeof(ans));
    n = recvfrom(sockfd, ans, sizeof(ans)-1, 0, (struct sockaddr *) &remote_addr, &len);
    ans[n] = 0;
    if (n < 0){
        perror("Errore di ricezione risposta registrazione dal server");
        return;
    }
    else printf("%s\n", ans);
}

void getSecret(){
    system("clear");
    printf("Di chi vuoi conoscere il segreto? ");
    scanf("%s", ans);
    sendto(sockfd, ans, strlen(ans)+1, 0, (struct sockaddr *) &remote_addr, len);
    memset(ans, 0, sizeof(ans));
    n = recvfrom(sockfd, ans, sizeof(ans)-1, 0, (struct sockaddr *) &remote_addr, &len);
    ans[n] = 0;
    if (n < 0){
        perror("Errore di ricezione risposta dal server");
        return;
    }
    else printf("\n%s\n", ans);
}

void setSecret(){
    system("clear");
    memset(ans, 0, sizeof(ans));
    n = recvfrom(sockfd, ans, sizeof(ans)-1, 0, (struct sockaddr *) &remote_addr, &len);
    printf("Vecchio segreto: %s\n", ans);
    printf("\nInserisci il nuovo segreto: ");
    scanf("%s", ans);
    sendto(sockfd, ans, strlen(ans)+1, 0, (struct sockaddr *) &remote_addr, len);
    n = recvfrom(sockfd, ans, sizeof(ans)-1, 0, (struct sockaddr *) &remote_addr, &len);
    ans[n] = 0;
    printf("%s\n", ans);
}

void setIps(){
    system("clear");
    memset(ans, 0, sizeof(ans));
    n = recvfrom(sockfd, ans, sizeof(ans)-1, 0, (struct sockaddr *) &remote_addr, &len);
    printf("Vecchie macchine autorizzate: %s\n", ans);
    printf("\nInserisci le nuove macchine (separa gli host con uno spazio): ");
    scanf("%s", ans);
    sendto(sockfd, ans, strlen(ans)+1, 0, (struct sockaddr *) &remote_addr, len);
    n = recvfrom(sockfd, ans, sizeof(ans)-1, 0, (struct sockaddr *) &remote_addr, &len);
    ans[n] = 0;
    printf("%s\n", ans);
}

void modifica(){
    system("clear");
    printf("Cosa vuoi modificare?\n");
    printf("1. Segreto\n2. Macchine autorizzate\n3. Annulla\n");
    memset(ans, 0, sizeof(ans));
    scanf("%s", ans);

    if(strcmp(ans, "1") == 0){
        sendto(sockfd, ans, strlen(ans)+1, 0, (struct sockaddr *) &remote_addr, len);
        setSecret();
    }
    else if(strcmp(ans, "2") == 0){
        sendto(sockfd, ans, strlen(ans)+1, 0, (struct sockaddr *) &remote_addr, len);
        setIps();
    }
    else if(strcmp(ans, "3") == 0){
        sendto(sockfd, ans, strlen(ans)+1, 0, (struct sockaddr *) &remote_addr, len);
        return;
    }
    else{
        printf("Scelta non valida\n");
        sleep(3);
        modifica();
        return;
    }
    sleep(3);
    modifica();
}

void loggedSeleziona(){
    system("clear");
    printf("Benvenuto %s, cosa vuoi fare?\n", loginfo.user);
    printf("1. Conoscere il segreto di un utente\n2. Modifica informazioni\n3. Logout\n");
    scanf("%s", ans);
    if(strcmp(ans, "1") == 0){
        sendto(sockfd, ans, strlen(ans)+1, 0, (struct sockaddr *) &remote_addr, len);
        getSecret();
    }
    else if(strcmp(ans, "2") == 0){
        sendto(sockfd, ans, strlen(ans)+1, 0, (struct sockaddr *) &remote_addr, len);
        modifica();
    }
    else if(strcmp(ans, "3") == 0){
        sendto(sockfd, ans, strlen(ans)+1, 0, (struct sockaddr *) &remote_addr, len);
        return;
    }
    else{
        printf("Scelta non valida\n");
        sleep(3);
        loggedSeleziona();
        return;
    }
    sleep(3);
    loggedSeleziona();
}

void login(){
    system("clear");
    printf("Inserisci il tuo nome utente: ");
    scanf("%s", loginfo.user);
    printf("Inserisci il tuo indirizzo IPv4: ");
    scanf("%s", loginfo.ip);

    sendto(sockfd, &loginfo, sizeof(loginfo), 0, (struct sockaddr *) &remote_addr, len);
    memset(ans, 0, sizeof(ans));
    n = recvfrom(sockfd, ans, sizeof(ans)-1, 0, (struct sockaddr *) &remote_addr, &len);
    ans[n] = 0;

    if (n < 0){
        perror("Errore di ricezione risposta dal server");
        return;
    }

    if(strcmp(ans, "ok") == 0){
        printf("Login effettuato con successo\n");
        sleep(1);
        loggedSeleziona();
        return;
    }
    printf("%s\n", ans);
}

void seleziona(){
    system("clear");
    printf("Cosa vuoi fare?\n");
    printf("1. Login\n2. Registrazione\n3. Esci\n");
    scanf("%s", ans);

    if(strcmp(ans, "1") == 0){
        sendto(sockfd, ans, strlen(ans)+1, 0, (struct sockaddr *) &remote_addr, len);
        login();
    }
    else if(strcmp(ans, "2") == 0){
        sendto(sockfd, ans, strlen(ans)+1, 0, (struct sockaddr *) &remote_addr, len);
        registrazione();
    }
    else if(strcmp(ans, "3") == 0){
        close(sockfd);
        terminator();
    }
    else if(strcmp(ans, "exit") == 0){
        sendto(sockfd, ans, strlen(ans)+1, 0, (struct sockaddr *) &remote_addr, len);
        close(sockfd);
        terminator();
    }
    else{
        printf("Scelta non valida\n");
        sleep(3);
        seleziona();
        return;
    }
    sleep(5);
}

int main(int argc, char** argv){
    child = fork();
    if(child == 0){
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

        recvfrom(sockfd, ans, sizeof(ans)-1, 0, (struct sockaddr *) &remote_addr, &len);
        if (strcmp(ans, "exit") == 0){
            close(sockfd);
            terminator();
        }       
    }
    else{
        sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if(sockfd < 0){
            perror("Errore nella creazione del socket");
            return -1;
        }

        memset(&remote_addr, 0, len);
        remote_addr.sin_family = AF_INET;
        remote_addr.sin_port = htons(atoi(port));
        inet_pton(AF_INET, ip, &remote_addr.sin_addr);

        while (1) seleziona();
    }
    return 0;
}

