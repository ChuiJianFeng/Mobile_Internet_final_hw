#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#define MAXBUF 1024
int main(int argc, char **argv){
        int sockfd, len;
        struct sockaddr_in serveraddr;
        char buffer[MAXBUF];
        if(argc != 2){
                printf("Usage: ./client port \n");
                exit(1);
        }
        int port = atoi(argv[1]);

                sockfd = socket( AF_INET, SOCK_STREAM, 0);
                if(sockfd == -1){
                        perror("socket");  // show error
                        exit(1);
                }

        bzero(&serveraddr,sizeof(serveraddr) );
        serveraddr.sin_family = AF_INET;
        serveraddr.sin_port = htons(port);
		if(inet_aton("127.0.0.1",(struct in_addr *) & serveraddr.sin_addr.s_addr) == 0){
                        printf("IP Address error\n");
                        exit(1);
                }
                if(connect(sockfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) !=0){
                        printf("connect error\n");
                        exit(1);
                }
                while(1){
		    printf("Client: \t");
		    scanf("%s", &buffer[0]);
		    send(sockfd, buffer, strlen(buffer), 0);
		    
		    if(strcmp(buffer, ":exit") == 0){
	    		 close(sockfd);
			 printf("[-]Disconnected from server.\n");							     
			 exit(1);
		    }
                    if(recv(sockfd, buffer, 1024, 0) < 0){
	   	         printf("[-]Error in receiving data.\n");
		    }else{
		    	 printf("Server: %s\n", buffer);
		    }		    
		}
		close(sockfd);
		 
        return 0;


}

