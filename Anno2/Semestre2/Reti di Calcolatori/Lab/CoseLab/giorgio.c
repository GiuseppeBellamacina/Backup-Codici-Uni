/*
** listener.c -- a datagram sockets "server" demo
*/

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define MYPORT "4950" // the port users will be connecting to

#define MAXUSERS 500

struct account {
  char username[32];
  char password[256];
};

struct users {
  struct account acc;
  char port[5];
  char token[32];
};

struct SystemMessage {
  int type; // 0: Token, 1: Reg error, 2: Usermessage, 3: Goodbye
  char message[512];
  char token[512];
};

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa) {
  if (sa->sa_family == AF_INET) {
    return &(((struct sockaddr_in *)sa)->sin_addr);
  }

  return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

void generateToken(char *token) {
  // Set the seed for the random number generator
  srand(time(NULL));

  // Generate four random 8-bit numbers and format them as a token string
  sprintf(token, "%02X%02X%02X%02X", rand() & 0xFF, rand() & 0xFF,
          rand() & 0xFF, rand() & 0xFF);
}

bool userExists(struct users *users, int userNumber, char username[512]) {
  for (int i = 0; i < userNumber; i++) {
    struct users tmpacc = users[i];
    if (strcmp(tmpacc.acc.username, username) == 0) {
      return true;
    }
  }

  return false;
}

bool tokenExists(struct users *users, int userNumber, char token[512]) {
  for (int i = 0; i < userNumber; i++) {
    struct users tmpacc = users[i];
    if (strcmp(tmpacc.token, token) == 0) {
      return true;
    }
  }

  return false;
}

char *tokenToUsername(struct users *users, int userNumber, char token[512]) { //Unsafe if token does not exist
  char *username;
  for (int i = 0; i < userNumber; i++) {
    struct users tmpacc = users[i];
    if (strcmp(tmpacc.token, token) == 0) {
      username = tmpacc.acc.username;
      return username;
    }
  }
  return username;
}

int main(void) {
  struct users users[MAXUSERS];
  int userNumber = 0;

  int sockfd;
  struct addrinfo hints, *servinfo, *p;
  int rv;
  int numbytes;
  char s[INET6_ADDRSTRLEN];

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET; // set to AF_INET to use IPv4
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_flags = AI_PASSIVE; // use my IP

  if ((rv = getaddrinfo(NULL, MYPORT, &hints, &servinfo)) != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
    return 1;
  }

  // loop through all the results and bind to the first we can
  for (p = servinfo; p != NULL; p = p->ai_next) {
    if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
      perror("listener: socket");
      continue;
    }

    if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
      close(sockfd);
      perror("listener: bind");
      continue;
    }

    break;
  }

  if (p == NULL) {
    fprintf(stderr, "listener: failed to bind socket\n");
    return 2;
  }

  freeaddrinfo(servinfo);

  printf("listener: waiting to recvfrom...\n");

  while (1) {
    struct account acc;
    struct sockaddr_storage their_addr;
    socklen_t addr_len;

    addr_len = sizeof their_addr;
    if ((numbytes = recvfrom(sockfd, &acc, sizeof(acc), 0,
                             (struct sockaddr *)&their_addr, &addr_len)) ==
        -1) {
      perror("recvfrom");
      exit(1);
    }

    printf("listener: got packet from %s\n",
           inet_ntop(their_addr.ss_family,
                     get_in_addr((struct sockaddr *)&their_addr), s, sizeof s));
    printf("listener: packet is %d bytes long\n", numbytes);
    printf("listener: received credentials: \"%s\", \"%s\"\n", acc.username,
           acc.password);

    bool flagged = userExists(users, userNumber, acc.username);

    if (flagged) {
      printf("Username already exists, sending packet");
      struct SystemMessage msg;
      strcpy(msg.message, "Username non disponibile");
      msg.type = 1;
      sendto(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *)&their_addr,
             addr_len);
      continue;
    }

    struct SystemMessage token;
    char *tokenString = malloc(sizeof(char[9]));
    generateToken(tokenString);
    strcpy(token.token, tokenString);
    token.type = 0;
    sendto(sockfd, &token, sizeof(token), 0, (struct sockaddr *)&their_addr,
           addr_len);
    
    printf("Registered ")

    while (1) {
      memset(&token, 0, sizeof(token));
      if ((numbytes = recvfrom(sockfd, &token, sizeof(token), 0,
                               (struct sockaddr *)&their_addr, &addr_len)) ==
          -1) {
        perror("recvfrom");
        exit(1);
      }
      if (token.type == 3) {
        if (tokenExists(users, userNumber, token.token)) {
          printf("Goodbye from %s", tokenToUsername(users, userNumber, token.token));
          break;
        }
      }

      if (token.type == 2) {
        // Send broadcast message, check if token exists
        if(!tokenExists(users, userNumber, token.token)) {
            printf("Got message from non-existing token: %s", token.token);
        }
        printf("<%s> %s", tokenToUsername(users, userNumber, token.token), token.message);
      }
    }
  }

  close(sockfd);

  return 0;
}