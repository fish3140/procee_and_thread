#include <stdio.h>
#include <stdlib.h>
#include<fcntl.h>
int main()
{
	int ret ;
	int fd;
	char line[16] ;

	fd = open("./fifo_tmp", O_RDONLY);
	while(1)
	{
		if(fd>0)
		{
			printf("open FIFO file succesed ...%d\n",getpid());
			read(fd,line,16);
			write(1,line,16);
		}

	}
		
	return 0;
}