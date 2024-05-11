/* UDP Sender */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char* argv[])
{ int sockfd;
  struct sockaddr_in dest_addr;
  extern int errno;
  int i,n;
  char buffer[100];
  
  if(argc < 3)
  {  printf("Use: sender IP_dest PORT_dest");
   return 0;
  }  
  
  if((sockfd=socket(PF_INET,SOCK_DGRAM,0)) <0)
  { printf("\nError in socket opening ... exit!");
    return -1;
  }
  
  memset( &dest_addr, 0, sizeof(dest_addr));
  dest_addr.sin_family = AF_INET;
  inet_pton(AF_INET, argv[1], &(dest_addr.sin_addr)); 
  dest_addr.sin_port = htons(atoi(argv[2]));
  
  printf("\nInsert an integer: ");
  scanf("%d",&n);

  for(i=0; i<10; ++i)
  { sprintf(buffer,"%d",i+n);
    printf("sending %s\n",buffer);
    sendto(sockfd, buffer, strlen(buffer)+1, 0, (struct sockaddr *) &dest_addr, sizeof(dest_addr));
  }
}