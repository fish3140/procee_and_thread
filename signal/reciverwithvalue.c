#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
void handler(int signum, siginfo_t *info, void * ucontext)
{
	printf("now has got the  sigal...\n");
	printf("send pid is %d...\n",info->si_pid);
	printf("send num %d...\n",info->si_int);
	kill(getpid(),SIGKILL);
	
}

int main()
{
	pid_t pid , pid_ch;
	int status;
	int i,ret;
	struct sigaction act ,oldact;
	act.sa_flags= SA_SIGINFO;
	act.sa_sigaction = handler;
	//pid = vfork(); //阻塞等待子进程结束，类似wait
	//signal(SIGUSR1,handler);
	sigaction(SIGUSR1, &act, &oldact);
	while(1)
	{
		printf("time is %d",i);
		i++;
		sleep(1);
	}
	return 0;
}

