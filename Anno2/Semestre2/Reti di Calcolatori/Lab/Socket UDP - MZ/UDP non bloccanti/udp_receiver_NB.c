/* UDP Receiver - Server NON_BLOCK*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char* argv[])
{ int sockfd;
  struct sockaddr_in local_addr, remote_addr;
  socklen_t len = sizeof(struct sockaddr_in);
  char buffer[256];
  
  if(argc < 2)
  {  printf("Use: receiver listening_PORT");
   return 0;
  }  
  
  if((sockfd=socket(PF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0)) <0)
  { printf("\nError in socket opening ... exit!");
    return -1;
  }
  memset((char *) &local_addr,0,len);
  local_addr.sin_family = AF_INET;
  //local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  local_addr.sin_port = htons(atoi(argv[1]));

  if(bind(sockfd, (struct sockaddr *) &local_addr, len)<0)
  { printf("\nBinding error! Error code n.%d \n",errno);
    return -1;
  }
  
  for(;;)
  { if ( recvfrom(sockfd, buffer, 99,0, (struct sockaddr *) &remote_addr, &len) >0) 
    {
        printf("Packet from IP:%s Port:%d msg:%s \n", inet_ntoa(remote_addr.sin_addr), ntohs(remote_addr.sin_port), buffer);
    }
    else
    {
        printf("\n");
        sleep(5);
    }
  }
}