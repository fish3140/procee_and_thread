#include <stdio.h>
#include <stdlib.h>
#include<fcntl.h>
int main()
{
	int ret ;
	int fd;
	char line[16] = "write start ....\n";
	ret = mkfifo("./fifo_tmp",0777);
	if(ret == 0 )
		printf("make FIFO file successed...\n");
	fd = open("./fifo_tmp", O_WRONLY);
	while(1)
	{
		if(fd>0)
		{
			printf("open FIFO file succesed ...%d\n",getpid());
			write(fd,line,16);
		}
		sleep(5);
	}
		
	return 0;
}