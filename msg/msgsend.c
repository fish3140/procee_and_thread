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
	memset(date.line , 0, 40);
	while(1)
	{
		
		read(0,date.line,5);
		date.msg_type= 8;
		printf("input date is %s \n",date.line);
		ret = msgsnd(msgid, (void *)&date, 40, 0);
		if(ret == -1 )
		{
			printf("send date failed ....\n");
			fprintf(stderr, "msgsnd failed\n");   
			exit(1);
		}
		if(strstr(date.line,"end") != NULL )
			break;
	}
	msgctl(msgid,IPC_RMID,0);
	
	return 0;
}