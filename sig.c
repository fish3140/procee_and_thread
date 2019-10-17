#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
void handler()
{
	printf("father has got sigal...\n");
	kill(getpid(),SIGKILL);
	
}
void chandler()
{
	printf("child has killed...\n");
}
int main()
{
	pid_t pid , pid_ch;
	int status;
	int i,ret;
	//pid = vfork(); //阻塞等待子进程结束，类似wait
	signal(SIGCHLD,chandler);
	pid = fork();
	if(pid<0)
	{
		printf("process build failed ...\n");
	}
	else{
		printf("process build sucess...pid is %d ppid is %d ...\n",getpid(),getppid());
		if(pid >0)
		{
			//exit(1);//父进程直接退出，子进程成为孤儿进程，由init（pid = 1）管理
			printf("is father...pid is %d ppid is %d ...\n",getpid(),getppid());
			//pid_ch = wait(&status);等待子进程完结，发送的信号，清理子进程
			//printf("now pid is %d...\n",pid_ch);
			//sleep(100);
			kill(pid,SIGKILL);
			sleep(2);
			wait(&status);
			//signal(SIGINT,handler);
			//while(1);
			printf("now pid is %d...\n",pid_ch);
		}
		if( pid == 0 )
		{
			sleep(100);
			/*守护进程操作
			
			setsid();
			chdir("/");
			umask(0);
			for(i=0;i<64;i++)
				close(i);
			printf("???is child...pid is %d ppid is %d ...\n",getpid(),getppid());
			sleep(100);
			*/
			//exit(1);
			//ret = execl("./pth.exe","pth",NULL);
			//if(ret == -1)
			//	printf("execl failed ...\n");
		printf("???is child...pid is %d ppid is %d ...\n",getpid(),getppid());
		}
	}
	return 0;
	
}