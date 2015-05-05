#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <fcntl.h>

#include <unistd.h>

#include <sys/types.h>

#include <sys/socket.h>

#include <sys/ipc.h>

#include <sys/wait.h>

#include <time.h>

#include <arpa/inet.h>

#include <netinet/in.h>

#include <netinet/ip.h>



#define SRV_IP "127.0.0.1"

int main(int argc, char **argv) {

    int sockfd, serv_len, n;

    struct sockaddr_in serv_addr;

    struct hostent *serv;

    char buf[512];



    struct {

        char sendline[512];

	char recvline[1000];

        int uuid;

    } msg_in, msg_out;

    

    /* Generate a random UUID */

    //srand(time(NULL));

   // uuid = rand();



  if ((sockfd=socket(AF_INET,SOCK_DGRAM,0)) < 0){

  	perror("error creating socket");

  }



   bzero(&serv_addr,sizeof(serv_addr));

   serv_addr.sin_family = AF_INET;

   serv_addr.sin_port=htons(32000);



  if (inet_aton(SRV_IP, &serv_addr.sin_addr)==0) {

         fprintf(stderr, "inet_aton() failed\n");

         exit(1);

  }

  while (fgets(msg_in.sendline, 10000,stdin) != NULL)

   {

      sendto(sockfd,msg_in.sendline,strlen(msg_in.sendline),0,

             (struct sockaddr *)&serv_addr,sizeof(serv_addr));

      n=recvfrom(sockfd,msg_in.recvline,10000,0,NULL,NULL);

      msg_in.recvline[n]=0;

      fputs(msg_in.recvline,stdout);

   }



}
