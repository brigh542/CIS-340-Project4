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



#define MAX_PACKET_SIZE 512



int main(int argc, char **argv){





struct Message{

	char *cmd;

	char *seq;

	char *number;

	char data[512];

	};

struct sockaddr_in serv_addr,cli_addr;

struct Message *msg = malloc(sizeof(struct Message));

int fd, connect, floppy,fsize;

socklen_t socksize = sizeof(struct sockaddr_in);





//creating a random UUID

//srand(time(NULL));

//serv_id = rand();







if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {

	perror("cannot create socket");

	return 0;

}



bzero(&serv_addr,sizeof(serv_addr));



 serv_addr.sin_family = AF_INET;

   serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);

   serv_addr.sin_port=htons(32000);



  if((bind(fd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)){

      perror("bind failed");

      return 0;

  }



  if((floppy = open("./imagefile.img", O_RDONLY)) < 0){

      perror("imagefile not mounted");

  }




   fsize = sizeof(cli_addr);

   connect = recvfrom(fd,msg,sizeof(*msg),0,(struct sockaddr *)&cli_addr,&fsize);
   

   if(connect < 0){

   perror("error recvfrom");

   return 0;

   }
   printf(msg);


close(fd);

close(connect);

return 0;

}
