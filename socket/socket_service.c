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
	sock = socket(AF_INET, SOCK_STREAM, 0);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(8000);
	bind(sock, (struct sockaddr *)&addr,sizeof(addr));
	listen(sock,5);
	while(1)
	{
		client_sock = accept(sock,(struct sockaddr*)&client_addr,&client_len);
		//接受client绑定，获取client socket文件描述符  
		read(client_sock,line,10);
		printf("client: %s ... \n",line);
		write(client_sock,"ok_got",10);
		close(client_sock);
	}
	return 0;
}