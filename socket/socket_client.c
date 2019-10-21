#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include <netinet/in.h>  
#include <arpa/inet.h> 

int main(int argc , int *argv[])
{
	int sock,client_sock;
	struct sockaddr_in addr,client_addr;
	int client_len;
	char line[10];
	int ret ;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(8000);
	//bind(sock, (struct sockaddr *)addr,sizeof(addr));
	//listen(sock,5);
	
	ret = connect(sock, (struct sockaddr*)&addr, sizeof(addr));  
	if(ret == -1)
		printf("connect failed ... \n");

	read(0,line,5);	
	write(sock,line,10);
	//printf("Line: %s ... \n",line);
	memset(line,0,10);
	read(sock,line,10);
	printf("service : %s ... \n",line);
	close(sock);
	return 0;
}