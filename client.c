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
#include <netdb.h>



#define SRV_IP "127.0.0.1"

int main(int argc, char **argv) {

    int sockfd, serv_len, n;

    struct sockaddr_in serv_addr;

    struct hostent *serv;

    char buf[512];
    char command[30], var[30], arg[30];



    struct {

        char sendline[512];

	char sector[30];

        int uuid;

    } msg_in, msg_out;

    

    /* Generate a random UUID */

    //srand(time(NULL));

   // uuid = rand();




while(1){
  printf("flop: ");
  fgets(command, 30, stdin);
  sscanf(command, "%s", var);
 if (strcmp("fmount", var) == 0){
   sscanf(command, "%s %s", var, arg);
   strcpy(msg_in.sendline,"CONNECT");

serv = gethostbyname(arg);

 if ((sockfd=socket(AF_INET,SOCK_DGRAM,0)) < 0){

  	perror("error creating socket");

  }



   bzero(&serv_addr,sizeof(serv_addr));

   serv_addr.sin_family = AF_INET;
   bcopy(serv->h_addr, (char *)&serv_addr.sin_addr, serv->h_length);

   serv_addr.sin_port=htons(696969);

   


  if (inet_aton(SRV_IP, &serv_addr.sin_addr)==0) {

         fprintf(stderr, "inet_aton() failed\n");

         exit(1);

  }
  serv_len = sizeof(serv_addr);
   sendto(sockfd,msg_in.sendline,strlen(msg_in.sendline),0,

             (struct sockaddr *)&serv_addr,sizeof(serv_addr));
}

 if (strcmp("fumount", var) == 0){
 	strcpy(msg_in.sendline,"DISCONNECT");
	sendto(sockfd,msg_in.sendline,strlen(msg_in.sendline),0,

             (struct sockaddr *)&serv_addr,sizeof(serv_addr));
	close(sockfd);
	printf("Disconnected");
}
 if (strcmp("quit", var) == 0){
    return 0;
}
 if (strcmp("showsector",var) == 0){
    sscanf(command, "%s %s", var, arg);
    strcpy(msg_in.sendline,var);
    strcpy(msg_in.sector,arg);
    sendto(sockfd,msg_in.sendline,strlen(msg_in.sendline),0,

             (struct sockaddr *)&serv_addr,sizeof(serv_addr));
    //recvfrom(sockfd,&msg_in.sendline,sizeof(msg_in.sendline),0,(struct sockaddr *)&serv_addr,&serv_len);
}

  //while (fgets(msg_in.sendline, 10000,stdin) != NULL)

  // {

      //sendto(sockfd,msg_in.sendline,strlen(msg_in.sendline),0,

         //    (struct sockaddr *)&serv_addr,sizeof(serv_addr));

     // n=recvfrom(sockfd,msg_in.recvline,10000,0,NULL,NULL);

     // msg_in.recvline[n]=0;

     // fputs(msg_in.recvline,stdout);

   //}

}

}
