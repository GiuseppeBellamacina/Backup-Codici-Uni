/* Simple UDP client */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

struct Message{
    char mess[100];
    int num;
};

int main(int argc, char**argv)
{ int sockfd, n;
  struct sockaddr_in remote_addr;
  char sendline[1000];
  char recvline[1000];
  socklen_t len = sizeof(struct sockaddr_in);
   
  if (argc != 3)
  { printf("usage:  UDPclient <remote_IP remote_port>\n");
    return 1;
  }

  if((sockfd=socket(AF_INET,SOCK_DGRAM,0)) <0)
  { printf("\nError in socket opening ... exit!");
    return -1;
  }
  
  memset(&remote_addr,0,len);
  remote_addr.sin_family = AF_INET;
  inet_pton(AF_INET, argv[1], &(remote_addr.sin_addr)); 
  remote_addr.sin_port=htons(atoi(argv[2]));
   
  while (1)
  { struct Message msg;
  fgets(msg.mess, 100, stdin);
  msg.mess[strcspn(msg.mess, "\n")] = '\0';
  scanf("%d", &msg.num);
  getchar();
  printf("%s - %d\n", msg.mess, msg.num);
    sendto(sockfd,&msg,sizeof(msg),0,
          (struct sockaddr *)&remote_addr, len);
    n=recvfrom(sockfd,&msg,sizeof(msg),0, (struct sockaddr *) &remote_addr, &len);
    recvline[n]=0;
	printf("From IP:%s Port:%d msg:%s num:%d \n", inet_ntoa(remote_addr.sin_addr),  ntohs(remote_addr.sin_port), msg.mess, msg.num);
  }
}