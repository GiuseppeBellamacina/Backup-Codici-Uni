/* Simple IPv6 UDP server  with bidirectional connection*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>

int main(int argc, char**argv)
{ int sockfd, n;
  char ipv6_addr[46];
  extern int errno;
  struct sockaddr_in6 local_addr, remote_addr;
  socklen_t len = sizeof(struct sockaddr_in6 );
  char mesg[1000];
   
  if(argc < 2)
  { printf("Use: server_ipv6 listening_PORT");
	  return 0;
  }	 

  if((sockfd=socket(AF_INET6,SOCK_DGRAM,0)) <0)
  { printf("\nError in socket opening ... exit!");
    return -1;
  }

  memset(&local_addr,0,sizeof(struct sockaddr_in6));
  local_addr.sin6_family = AF_INET6;
  local_addr.sin6_port = htons(atoi(argv[1]));
  if(bind(sockfd, (struct sockaddr *) &local_addr, len)<0)
  { printf("\nBinding error! Error code n.%d \n",errno);
    return -1;
  }

  for (;;)
  { n = recvfrom(sockfd,mesg,999,0,(struct sockaddr *) &remote_addr,&len);
    mesg[n] = 0;
    inet_ntop(AF_INET6, &(remote_addr.sin6_addr), ipv6_addr, INET6_ADDRSTRLEN);
	  printf("From IPv6:%s Port:%d msg:%s \n", ipv6_addr,  ntohs(remote_addr.sin6_port), mesg);
	  sendto(sockfd,mesg,n,0,(struct sockaddr *)&remote_addr,len);
  }
}
