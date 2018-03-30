#include <stdio.h>
#include <sys/socket.h>

int main(){
	int sockfd;
	struct sockaddr_in info;
	sockfd = socket(AF_INET,SOCK_STREAM,0);

	if( sockfd == -1 ){
		printf("Fail to create a socket.");
	}
	
	bzero(&info,sizeof(info));
	info.sin_family = PF_INET;
	info.sin_addr.s_addr = inet_addr(ip);
	info.sin_port = htons(port);
	int err = connect(sockfd,(struct sockaddr*)&info,sizeof(info));
	if(err == -1){
		printf("Connection error.");
	}
	return 0;
}
