#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
void handler()
{
	printf("now has got the  sigal...\n");
	kill(getpid(),SIGKILL);
	
}

int main()
{
	pid_t pid , pid_ch;
	int status;
	int i,ret;
	//pid = vfork(); //阻塞等待子进程结束，类似wait
	signal(SIGUSR1,handler);
	while(1)
	{
		printf("time is %d",i);
		i++;
		sleep(1);
	}
	return 0;
}

