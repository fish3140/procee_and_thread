#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/msg.h>
struct msg_da{
	long int msg_type;
	char line[10];
};

int main(int argc, int *argv[])
{
	key_t key;
	int msgid;
	struct msg_da date;
	int ret ;
	int msgtype = 0;
	key = ftok("./ca", 'o');
	if(key<0)
		printf("key make failed ...\n");
	msgid = msgget(key, IPC_CREAT|0666);
	if(msgid < 0)
	{
		printf("msg make failed ...\n");
		if(errno == EEXIST)
		{
			printf("file exit ...\n");
			msgid = msgget(key, 0666);
		}
		else{
			 perror("msgget failed");
			 exit(1);
		}
	
	}
	//sleep(5);
	msgtype = 8;
	while(1)
	{
		
		ret = msgrcv(msgid, (void *)&date,40, msgtype, 0);
		if(ret == -1 )
		{
			printf("rcv date failed ....\n");
			exit(1);
		}
		printf("RCV : recive date is %s....\n",date.line);
		if(strstr(date.line,"end") != NULL )
			break;
	}
	msgctl(msgid,IPC_RMID,0);
	
	return 0;
}