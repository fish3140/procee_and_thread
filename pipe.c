#include <stdio.h>
#include <stdlib.h>
int main()
{
	pid_t pid , pid_ch;
	int status;
	int i,ret;
	int fd[2]; 
	char line[128];
	if(pipe(fd)<0) //0 --->读描述符， 1 -->写描述符
		printf("pipe create failed ... \n");
	pid = fork();
	if(pid<0)
		printf("fork failed...\n");
	else
	{
		if(pid > 0)
		{
			printf("father successed...%d\n",getpid());
			close(fd[1]);
			read(fd[0],line,128);
			write(1,line,128);
			pid_ch = wait(&status);
			printf("child is %d...\n",pid_ch);
			
			
		}
		if(pid == 0 )
		{
			printf("child successed...%d\n",getpid());
			sleep(5);
			close(fd[0]);
			write(fd[1],"hello ... pipe has successed ...happy...",30);
			exit(0);
		}
	}
	return 0;
	
}