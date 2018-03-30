#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int port;
int main(){
	char inputBuffer[256] = {};
	char message[] = {"Hi,this is server.\n"};
	int sockfd = 0,Clientfd = 0;
	struct sockaddr_in serverinfo,clientinfo;
	int addrlen = sizeof(clientinfo);

	/*	socket 建立	*/
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if( sockfd == -1 ){
		printf("Fail to create a socket.");
	}
	
	bzero(&serverinfo,sizeof(serverinfo));
	serverinfo.sin_family = PF_INET;
	serverinfo.sin_addr.s_addr = INADDR_ANY;
	serverinfo.sin_port = htons(port);
	bind(sockfd,(struct sockaddr*)&serverinfo,sizeof(serverinfo));
	listen(sockfd,10);
	
	while(1){
		Clientfd = accept(sockfd,(struct sockaddr*)&clientinfo,&addrlen);
		send(Clientfd,message,sizeof(message),0);
		recv(Clientfd,inputBuffer,sizeof(inputBuffer),0);
		printf("Get:%s\n",inputBuffer);
	
	}
	return 0;
}
