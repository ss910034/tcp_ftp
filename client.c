#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

char commands[20]={};
char ip[20]={};
char port[10]={};
char filename[20]={};
void welcome();
int main(int argc , char *argv[])
{

    //socket的建立
    int sockfd = 0;
    sockfd = socket(AF_INET , SOCK_STREAM , 0);

    if (sockfd == -1){
        printf("Fail to create a socket.");
    }
	welcome();
    //socket的連線

    struct sockaddr_in info;
    bzero(&info,sizeof(info));
    info.sin_family = PF_INET;

    //localhost test
    info.sin_addr.s_addr = inet_addr("127.0.0.1");
    info.sin_port = htons(4434);


    int err = connect(sockfd,(struct sockaddr *)&info,sizeof(info));
    if(err==-1){
        printf("Connection error");
    }


    //Send a message to server
    char message[] = {"Hi there"};
    char receiveMessage[100] = {};
    send(sockfd,message,sizeof(message),0);
     recv(sockfd,receiveMessage,sizeof(receiveMessage),0);

    printf("%s",receiveMessage);
    printf("close Socket\n");
    close(sockfd);
    return 0;
}
void welcome(){
    printf("Welcome to my program!\nYou can use three commands.(login ip port,upload filename,logout)\n");
    printf("Please enter your commands : ");
    scanf("%s",commands);
	if( strcmp(commands,"login")==0 ){
		scanf("%s%s\n",ip,port);
		printf("%s %s %s",commands,ip,port);
	}
	else if( strcmp(commands,"upload")==0 ){
		scanf("%s\n",filename);
	}
	else if( strcmp(commands,"logout")==0 ){
	
	}
	else
		printf("You enter a wrong command\n");
}
