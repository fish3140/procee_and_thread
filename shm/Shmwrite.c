#include <stdio.h>
#include <stdlib.h>
#include<fcntl.h>
#include <sys/shm.h>
int main()
{
	int ret ;
	int fd;
	key_t key;
	int shmid;
	char line[16] = "write start ....\n";
	char *p = NULL;
	key = ftok("./tmp", 'a');
	printf("...key is %d ... \n",key);
	if(key < 0 )
		printf("make key value failed...\n");
	shmid = shmget(key, getpagesize(), IPC_CREAT|IPC_EXCL|0777);
	if(shmid < 0 )
	{
		printf("share memory buid failed...try to get it \n");
		shmid = shmget(key, getpagesize(), 0777); 
		if(shmid < 0 )
			printf("share memory some wrong happened ... \n");
	}	
	p = (char *)shmat(shmid, NULL,0);
	if(p == (char *)-1)
	{
		printf("shmat memory  failed...\n");
		exit(1);
	}
	sscanf("1234567","%s",p);
	sleep(10);	
	shmdt(p); //解除映射
	shmctl(shmid, IPC_RMID, 0); //删除共享内存
	return 0;
}