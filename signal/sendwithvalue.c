#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


int main(int argc,int *argv[])
{
	pid_t pid , pid_ch;
	int status;
	int i,ret;
	//pid = vfork(); //阻塞等待子进程结束，类似wait
	union sigval value;
	value.sival_int =  100;
	sscanf(argv[1],"%d",&pid);
	//ret = kill(pid,SIGUSR1);
	ret = sigqueue(pid, SIGUSR1, value);
	if(ret != 0)
	{
		printf("send signalfailed ... \n");
	}

	return 0;
	
}