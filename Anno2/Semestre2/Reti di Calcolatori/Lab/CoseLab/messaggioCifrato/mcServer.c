#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int sockfd, n;
struct sockaddr_in local_addr, remote_addr;
socklen_t len = sizeof(struct sockaddr_in);
FILE *file;
char ans[100];
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

struct FileReader{
    struct Login login;
    char secret[50];
    char ips[30];
};

struct FileReader reader;
struct Login loginfo;

void registrazione(){
    printf("Server ON: registrazione in corso\n");
    fflush(stdout);
    struct Registrazione reg;
    n = recvfrom(sockfd, &reg, sizeof(reg), 0, (struct sockaddr *) &remote_addr, &len);
    if(n < 0){
        printf("Errore di ricezione nuovo utente dall'host %s", inet_ntoa(remote_addr.sin_addr));
        return;
    }

    if ((file = fopen("users.txt", "a+")) == NULL){
        perror("Errore nell'apertura del file");
        return;
    }
    char line[200];
    while (fgets(line, sizeof(line), file)){
        char *token = strtok(line, "_");
        if(token != NULL) strcpy(line, token);
        if(strcmp(line, reg.user) == 0){
            strcpy(ans, "ERRORE: utente gi? registrato");
            sendto(sockfd, ans, strlen(ans)+1, 0, (struct sockaddr *) &remote_addr, len);
            fclose(file);
            return;
        }
    }
    fprintf(file, "%s_%s_%s_%s\n", reg.user, inet_ntoa(remote_addr.sin_addr), reg.secret, reg.ips);
    fclose(file);
    strcpy(ans, "Registrazione avvenuta con successo");
    sendto(sockfd, ans, strlen(ans)+1, 0, (struct sockaddr *) &remote_addr, len);
}

int isAuthorized(char *host, char *otherHost){
    // muove la testina di lettura del file all'inizio
    char line[200];
    fseek(file, 0, SEEK_SET);
    // fileReader reader e' una struttura che contiene i dati letti dal file
    while (fgets(line, sizeof(line), file)){
        char *token = strtok(line, "_");
        if(token != NULL) strcpy(reader.login.user, token);
        token = strtok(NULL, "_");
        if(token != NULL) strcpy(reader.login.ip, token);
        token = strtok(NULL, "_");
        if(token != NULL) strcpy(reader.secret, token);
        token = strtok(NULL, "\n");
        if(token != NULL) strcpy(reader.ips, token);

        if(strcmp(reader.login.user, otherHost) == 0){
            if(strstr(reader.ips, host) != NULL){ // l'utente e' autorizzato a ricevere il segreto
                return 1;
            }
            else return 0;
        }
        else continue;   
    }
    return 0;
}

int itExists(char *host){
    char line[200];
    char tmp[50];
    char *token;
    fseek(file, 0, SEEK_SET);
    while(fgets(line, sizeof(line), file)){
        token = strtok(line, "_");
        if(token != NULL) strcpy(tmp, token);
        if(strcmp(tmp, host) == 0) return 1;
        else continue;
    }
    return 0;
}

void sendSecret(){
    memset(ans, 0, sizeof(ans));
    n = recvfrom(sockfd, ans, sizeof(ans)-1, 0, (struct sockaddr *) &remote_addr, &len);
    ans[n] = 0;
    // controlla se esiste la macchina di cui si vuole conoscere il segreto
    if(itExists(ans)){
        if(isAuthorized(loginfo.user, ans)){
            sendto(sockfd, reader.secret, strlen(reader.secret)+1, 0, (struct sockaddr *) &remote_addr, len);
            fclose(file);
            return;
        }
        else{ // l'utente non e' autorizzato a ricevere il segreto
            strcpy(ans, "ERRORE: non sei autorizzato a ricevere il segreto");
            sendto(sockfd, ans, strlen(ans)+1, 0, (struct sockaddr *) &remote_addr, len);
            fclose(file);
            return;
        }
    }
    else{ // non esiste la macchina di cui si vuole sapere il segreto
        strcpy(ans, "ERRORE: non eiste la macchina da te specificata");
        sendto(sockfd, ans, strlen(ans)+1, 0, (struct sockaddr *) &remote_addr, len);
        fclose(file);
    }
}

void setSecret(){
    printf("Modifica segreto in corso...\n");
    fflush(stdout);
    // invio del vecchio segreto
    sendto(sockfd, reader.secret, strlen(reader.secret)+1, 0, (struct sockaddr *) &remote_addr, len);
    // ricezione del nuovo segreto
    memset(ans, 0, sizeof(ans));
    n = recvfrom(sockfd, ans, sizeof(ans)-1, 0, (struct sockaddr *) &remote_addr, &len);
    if(n < 0){
        printf("Errore di ricezione dal client %s", inet_ntoa(remote_addr.sin_addr));
        return;
    }
    // ans contiene il nuovo segreto
    // aggiornamento del file
    FILE *tmp;
    if ((tmp = fopen("tmp.txt", "w")) == NULL){
        perror("Errore nell'apertura del file");
        return;
    }
    char line[200];
    char user[20];
    strcpy(user, reader.login.user);
    fseek(file, 0, SEEK_SET);
    while(fgets(line, sizeof(line), file)){
        char *token = strtok(line, "_");
        if(token != NULL) strcpy(reader.login.user, token);
        token = strtok(NULL, "_");
        if(token != NULL) strcpy(reader.login.ip, token);
        token = strtok(NULL, "_");
        if(token != NULL) strcpy(reader.secret, token);
        token = strtok(NULL, "\n");
        if(token != NULL) strcpy(reader.ips, token);

        if(strcmp(reader.login.user, user) == 0){
            fprintf(tmp, "%s_%s_%s_%s\n", reader.login.user, reader.login.ip, ans, reader.ips);
        }
        else fprintf(tmp, "%s_%s_%s_%s\n", reader.login.user, reader.login.ip, reader.secret, reader.ips);
    }
    fclose(file);
    fclose(tmp);
    remove("users.txt");
    rename("tmp.txt", "users.txt");
    // invio conferma
    memset(ans, 0, sizeof(ans));
    strcpy(ans, "Modifica effettuata con successo");
    sendto(sockfd, ans, strlen(ans)+1, 0, (struct sockaddr *) &remote_addr, len);
}

void setIps(){
    printf("Modifica macchine autorizzate in corso...\n");
    fflush(stdout);
    // invio del vecchio elenco di macchine
    sendto(sockfd, reader.ips, strlen(reader.ips)+1, 0, (struct sockaddr *) &remote_addr, len);
    // ricezione del nuovo elenco di macchine
    memset(ans, 0, sizeof(ans));
    n = recvfrom(sockfd, ans, sizeof(ans)-1, 0, (struct sockaddr *) &remote_addr, &len);
    if(n < 0){
        printf("Errore di ricezione dal client %s", inet_ntoa(remote_addr.sin_addr));
        return;
    }
    // ans contiene il nuovo elenco di macchine
    // aggiornamento del file
    FILE *tmp;
    if ((tmp = fopen("tmp.txt", "w")) == NULL){
        perror("Errore nell'apertura del file");
        return;
    }
    char line[200];
    char user[20];
    strcpy(user, reader.login.user);
    fseek(file, 0, SEEK_SET);
    while(fgets(line, sizeof(line), file)){
        char *token = strtok(line, "_");
        if(token != NULL) strcpy(reader.login.user, token);
        token = strtok(NULL, "_");
        if(token != NULL) strcpy(reader.login.ip, token);
        token = strtok(NULL, "_");
        if(token != NULL) strcpy(reader.secret, token);
        token = strtok(NULL, "\n");
        if(token != NULL) strcpy(reader.ips, token);

        if(strcmp(reader.login.user, user) == 0){
            fprintf(tmp, "%s_%s_%s_%s\n", reader.login.user, reader.login.ip, reader.secret, ans);
        }
        else fprintf(tmp, "%s_%s_%s_%s\n", reader.login.user, reader.login.ip, reader.secret, reader.ips);
    }
    fclose(file);
    fclose(tmp);
    remove("users.txt");
    rename("tmp.txt", "users.txt");
    // invio conferma
    memset(ans, 0, sizeof(ans));
    strcpy(ans, "Modifica effettuata con successo");
    sendto(sockfd, ans, strlen(ans)+1, 0, (struct sockaddr *) &remote_addr, len);
}

void modifica(){
    printf("Modifica in attesa...\n");
    fflush(stdout);
    memset(ans, 0, sizeof(ans));
    n = recvfrom(sockfd, ans, sizeof(ans)-1, 0, (struct sockaddr *) &remote_addr, &len);
    ans[n] = 0;
    if(strcmp(ans, "1") == 0) setSecret();
    else if(strcmp(ans, "2") == 0) setIps();
    else if(strcmp(ans, "3") == 0) return;
    else perror("ERRORE: comando non valido");
    modifica();
}

void login(){
    printf("Server ON: login in corso\n");
    fflush(stdout);
    n = recvfrom(sockfd, &loginfo, sizeof(loginfo), 0, (struct sockaddr *) &remote_addr, &len);
    if(n < 0){
        printf("Errore di ricezione nuovo utente dall'host %s", inet_ntoa(remote_addr.sin_addr));
        return;
    }

    if(strcmp(loginfo.ip, inet_ntoa(remote_addr.sin_addr)) != 0){ // l'utente invia un IP non suo
        strcpy(ans, "ERRORE: non hai inviato il tuo IP");
        sendto(sockfd, ans, strlen(ans)+1, 0, (struct sockaddr *) &remote_addr, len);
        fclose(file);
        return;
    }

    if ((file = fopen("users.txt", "r")) == NULL){
        perror("Errore nell'apertura del file");
        return;
    }
    fseek(file, 0, SEEK_SET);

    char line[200];
    while(fgets(line, sizeof(line), file)){
        char *token = strtok(line, "_");
        if(token != NULL) strcpy(reader.login.user, token);
        token = strtok(NULL, "_");
        if(token != NULL) strcpy(reader.login.ip, token);
        token = strtok(NULL, "_");
        if(token != NULL) strcpy(reader.secret, token);
        token = strtok(NULL, "\n");
        if(token != NULL) strcpy(reader.ips, token);
        if(strcmp(loginfo.user, reader.login.user) == 0){
            if(strcmp(loginfo.ip, reader.login.ip) == 0){
                strcpy(ans, "ok");
                sendto(sockfd, ans, strlen(ans)+1, 0, (struct sockaddr *) &remote_addr, len);
                while(1){
                    n = recvfrom(sockfd, ans, sizeof(ans)-1, 0, (struct sockaddr *) &remote_addr, &len);
                    ans[n] = 0;
                    if(n < 0){
                        printf("Errore di ricezione dall'host %s", inet_ntoa(remote_addr.sin_addr));
                        return;
                    }
                    if(strcmp(ans,"1") == 0){
                        sendSecret();
                    }
                    else if(strcmp(ans, "2") == 0){
                        modifica();
                    }
                    else if(strcmp(ans, "3") == 0) return;
                    else perror("ERRORE: comando non valido");
                }
            }
            else{ // l'utente manda il suo ip, ma il nome dell'host e' errato
                strcpy(ans, "ERRORE: username errato");
                sendto(sockfd, ans, strlen(ans)+1, 0, (struct sockaddr *) &remote_addr, len);
                fclose(file);
                return;
            }
        }
        else continue;
    }
    // non trova l'utente nel file
    strcpy(ans, "ERRORE: utente non trovato");
    sendto(sockfd, ans, strlen(ans)+1, 0, (struct sockaddr *) &remote_addr, len);
    fclose(file);
}

void exitAll(){
    printf("Chiusura sistema in corso...\n");
    fflush(stdout);

    memset(&remote_addr, 0, len);
    remote_addr.sin_family = AF_INET;
    remote_addr.sin_port = htons(atoi(port));

    if ((file = fopen("users.txt", "r")) == NULL){
        perror("Errore nell'apertura del file");
        return;
    }

    char line[200];
    while(fgets(line, sizeof(line), file)){
        char *token = strtok(line, "_");
        char tmp[30];
        if(token != NULL) strcpy(tmp, token);
        token = strtok(NULL, "_");
        char ip[30];
        if(token != NULL) strcpy(ip, token);
        inet_pton(AF_INET, ip, &remote_addr.sin_addr); // cambio indirizzo a cui inviare il messaggio
        strcpy(ans, "exit");
        sendto(sockfd, ans, strlen(ans)+1, 0, (struct sockaddr *) &remote_addr, len);
        printf("Host %s <%s> chiuso\n", tmp, ip);
    }
    printf("Chiusura completata\n");
}

void seleziona(){
    printf("Server in attesa...\n");
    fflush(stdout);
    memset(ans, 0, sizeof(ans));
    n = recvfrom(sockfd, ans, sizeof(ans)-1, 0, (struct sockaddr *) &remote_addr, &len);
    ans[n] = 0;
    if(strcmp(ans, "1") == 0) login();
    if(strcmp(ans, "2") == 0) registrazione();
    else if(strcmp(ans, "exit") == 0){
        exitAll();
        close(sockfd);
        exit(0);
    }
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
    while (1) seleziona();
    return 0;
}

