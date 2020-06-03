#include<stdio.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<errno.h>
#include "circular_queue.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>

/*typedef struct Package Package;
struct Package{
    int dist;
    char content[100];
};*/

//static Package *test_var;

int main(int argc, char **argv){


    Cir_queue buffer;
    init_Cir_queue(&buffer);
    char buf[1024];


    //bulid socket
    int sockfd,forclientsockfd;
    int len;
    unsigned long int count = 1;
    
    pid_t childpid;


//    test_var = mmap(NULL, sizeof(Package)*3, PROT_READ | PROT_WRITE,
//                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);
//    test_var[0].dist = 0;
//    test_var[0].content[0] = buf[0];
	    
    if(argc != 2){
        printf("Usage : portno");
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int port = atoi(argv[1]);

    if(sockfd == -1){
        printf("Fail to creat a socket");
    }
    
    //socket connection
    struct sockaddr_in myaddr,forclientaddr;
    bzero(&myaddr, sizeof(myaddr));

    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(port);
    myaddr.sin_addr.s_addr = INADDR_ANY;

    if(bind(sockfd, (struct sockaddr *) &myaddr, sizeof(struct sockaddr)) ==-1){
        printf("bind error\n");
        exit(1);
    }
    if(listen(sockfd, 5) == -1){
    	printf("listen error");
	    exit(1);
    }

    while(1){
    	printf("---accept connection...\n");
        len = sizeof(struct sockaddr);
        forclientsockfd = accept(sockfd, (struct sockaddr *) &forclientaddr, &len);
        printf("Connection accepted from %s:%d\n", inet_ntoa(forclientaddr.sin_addr), ntohs(forclientaddr.sin_port));

        if(forclientsockfd == -1){
            if(errno == EINTR)
                    continue;
            else{
                perror("error");
                exit(1);
            }
	}

	if( (childpid = fork()) == 0 ){
            
	    close(sockfd);
        //test_var[0].dist = 1;
	    printf("child pid%d\n",getpid());
	    
	    while(1){
	    	recv(forclientsockfd ,buf, 1024,0);
            if(Cir_queue_full(&buffer) == true){
                (void)Cir_queue_pop(&buffer);
            }

                Cir_queue_push(&buffer, buf[0]);
            if(strcmp(buf, ":exit") == 0 ){
                printf("disconnect from %s %d \n", inet_ntoa(forclientaddr.sin_addr), ntohs(forclientaddr.sin_port));
                exit(1);
            }else{
                printf("Client_pid: %d\n",getpid());
                Cir_queue_print(&buffer);
                send(forclientsockfd, buf, strlen(buf), 0);
                bzero(buf, sizeof(buf));
            }
	    }

	}/*else{
            wait(NULL);
            printf("%d\n%s", test_var[0].dist, test_var[0].content);
            munmap(test_var, sizeof *test_var);
	}*/
	close(forclientsockfd);
		
    }
    return 0;
}
