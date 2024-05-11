#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER 1
#define CLIENT 0

int sockfd, n;
struct sockaddr_in local_addr, remote_addr;
socklen_t len = sizeof(struct sockaddr_in);
FILE *file;
char dest_ip[20] = "";
char my_port[20] = "8000";
char dest_port[20] = "7000";

struct Request{
    int n;
    int languageNumber;
    char languageName[10];
    char message[20];
};

struct Request req;

int distances[6][6] = {
        {0, 10, 50, 100, 150, 200}, // C
        {10, 0, 90, 140, 190, 240}, // C++
        {50, 90, 0, 130, 180, 230}, // Java
        {100, 140, 130, 0, 170, 220}, // Python
        {150, 190, 180, 170, 0, 210}, // R
        {200, 240, 230, 220, 210, 0} // Matlab
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

int* find_min_index(int distances[6][6], int row, int n){
    int* min_index = malloc(n * sizeof(int));
    // copy the row of the matrix in a tmp array
    int tmp[6];
    for(int i = 0; i < 6; i++) tmp[i] = distances[row][i];
    // sort tmp with selection sort
    for(int i = 0; i < 6; i++){
        int min = i;
        for(int j = i + 1; j < 6; j++){
            if(tmp[j] < tmp[min]) min = j;
        }
        int tmp2 = tmp[i];
        tmp[i] = tmp[min];
        tmp[min] = tmp2;
    }
    // shift every element of tmp to left
    for(int i = 0; i < 6; i++) tmp[i] = tmp[i + 1];
    tmp[5] = 0;
    // find the indexes of the first n elements of tmp in the row of the matrix
    int j = 0;
    for(int i = 0; i < 6; i++){
        if(j == n) break;
        if(distances[row][i] == tmp[j]){
            min_index[j++] = i;
            i = -1;
        }
    }
    return min_index;
}

void send_reply(){
    int* min_index = find_min_index(distances, req.languageNumber, req.n);
    char line[100];
    // read the file and send the reply to the client with languageNumber in min_index
    for(int i = 0; i < req.n; i++){
        // move the file pointer to the beginning of the file
        fseek(file, 0, SEEK_SET);
        while(fgets(line, sizeof(line), file)){
            char *token = strtok(line, " ");
            strcpy(dest_ip, token);
            token = strtok(NULL, " ");
            char dest[20];
            strcpy(dest, token);
            token = strtok(NULL, "\n");
            if(atoi(token) == min_index[i]){
                create_socket(CLIENT);
                sendto(sockfd, &req, sizeof(req), 0, (struct sockaddr *) &remote_addr, len);
                printf("Messaggio inviato a \33[1;34mVMClient %s\33[0m\n", dest);
                close(sockfd);
                break;
            }
        }
    }
    fclose(file);
    free(min_index); // dealloca min_index
}

void recv_request(){
    create_socket(SERVER);
    recvfrom(sockfd, &req, sizeof(req), 0, (struct sockaddr *) &remote_addr, &len);
    printf("\33[1;34mVMClient %s\33[0m chiede di inviare a %d client il messaggio \"%s\"\n", req.languageName, req.n, req.message);
    close(sockfd);
    // check if the machine is registered on file
    if((file = fopen("machines.txt", "a+")) == NULL){
        printf("\33[1;31mErrore nell'apertura del file\n\33[0m");
        exit(1);
    }
    char line[100];
    int found = 0;
    while(fgets(line, sizeof(line), file) != NULL){
        if(strstr(line, inet_ntoa(remote_addr.sin_addr)) != NULL){
            found = 1;
            break;
        }
    }
    if(found) send_reply();
    else{ // if the machine is not registered, add it to the file
        fprintf(file, "%s %s %d\n", inet_ntoa(remote_addr.sin_addr), req.languageName, req.languageNumber);
        send_reply();
    }
}

int main(int argc, char **argv){
    system("clear");
    while(1) recv_request();
    return 0;
}