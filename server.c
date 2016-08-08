#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#define MAX_MESSAGE 100
#define MAX_SOCK 100

int ClientSock[MAX_SOCK];

int main(int argc,char **argv){
	struct sockaddr_in sin,cin;
	int l_fd,c_fd;
	socklen_t len;
	char buf[MAX_MESSAGE];
	char addr_p[INET_ADDRSTRLEN];
	int port=5000;
	int n;
	bzero(&sin,sizeof(sin));
	bzero(&len,sizeof(len));
	sin.sin_family=AF_INET;
	sin.sin_addr.s_addr=INADDR_ANY;
	sin.sin_port=htons(port);

	if((l_fd=socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("fail to create listen socket");	
		exit(1);
	}
	if(bind(l_fd,(struct sockaddr *)&sin,sizeof(sin))==-1){
		perror("fail to bind");
		exit(1);
	}
	if(listen(l_fd,MAX_SOCK)==-1){
		perror("fail to listen");
		exit(1);
	}
	printf("waiting...\n");
	int temp=0;
	while(1){
		printf("accepting socket\n");
		if(temp==0){
		if((c_fd=accept(l_fd,(struct sockaddr *)&cin,&len))==-1){
			perror("fail to accept");
			exit(1);
		}
		temp=1;
		}
		printf("c_fd=%d\n",c_fd);
		n=recv(c_fd,buf,MAX_MESSAGE,0);
		if(n==-1){
			perror("fail to receive");
			exit(1);
		}else if(n==0){
			printf("the connect has been closed.\n");
			close(c_fd);
			continue;
		}
		inet_ntop(AF_INET,&cin.sin_addr,addr_p,sizeof(addr_p));
		printf("client IP %s,port is %d\n",addr_p,ntohs(cin.sin_port));
		printf("content is %s\n",buf);
		n=send(c_fd,buf,strlen(buf)+1,0);
		if(n==-1){
			perror("fail to send");
			exit(1);
		}
		/*if(close(c_fd)==-1){
			perror("fail to close");
			exit(1);
		}*/
		
	}
	return 0;	
}
