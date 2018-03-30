#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
int main(){
	int sockfd = 0;
	char receive[100]={};
	char ip[20];
	int port;
	char message[]={"Hi"};
	struct sockaddr_in info;	

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1){
		printf("Fail to create a socket.\n");
	}
	
	bzero(&info,sizeof(info));
	info.sin_family = PF_INET;
	info.sin_addr.s_addr = inet_addr(ip);
	info.sin_port = htons(port);
	
	int err = connect(sockfd,(struct sockaddr * )&info,sizeof(info));	 if(err == -1)
		printf("Connection error\n");
	
	send(sockfd,message,sizeof(message),0);
	recv(sockfd,receive,sizeof(receive),0);
	printf("%s",receive);
	close(sockfd);
	return 0;
}
