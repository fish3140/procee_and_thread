#include <stdio.h>
#include <stdlib.h>
#include<fcntl.h>

#include <sys/sem.h>
union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *arry;
};

//出初始化函数
int  init_semvalue(int semid,int num,int value)
{
	union semun arg ;
	int ret ;
	arg.val = value;
	
	ret = semctl (semid,num,SETVAL , arg );
	if(ret == -1)
		return -1;
	return 1;
	
}

//P操作 - 加锁
int sem_P(int semid,int num)
{
	int ret ;
	struct sembuf opsptr;
	opsptr.sem_num = num;
	opsptr.sem_op =  -1;
	ret = semop (semid, &opsptr, 1);//V操作 +
	if(ret == -1)
		return -1;
	return 1;
}
//V操作 释放锁+
int sem_V(int semid,int num)
{
	int ret ;
	struct sembuf opsptr;
	opsptr.sem_num = num;
	opsptr.sem_op =  1;
	ret = semop (semid, &opsptr, 1);//V操作 +
	if(ret == -1)
		return -1;
	return 1;
}
//删除
int  del_semvalue(int semid,int num)
{
	union semun arg ;
	int ret ;
	
	ret = semctl (semid, num,IPC_RMID ,arg );
	if(ret == -1)
		return -1;
	return 1;
	
}


int main()
{
	int ret ;
	int fd;
	key_t key;
	int sem_my = -1;
	char line[16] = "write start ....\n";
	char *p = NULL;
	key = ftok("./tm", 'a');
	printf("...key is %d ... \n",key);
	if(key < 0 )
		printf("make key value failed...\n");
	//shmid = shmget(key, getpagesize(), IPC_CREAT|IPC_EXCL|0777);
	//sem_my = semget((key_t)12345, 1, IPC_CREAT|0666);
	//创建打开信号量
	if(sem_my < 0 )
	{
		printf("sem create failed  \n");
		sem_my = semget((key_t)12345, 1, 0);
		//信号量作为临界资源，应该在另一进程执行P,V操作之前获取，执行P操作后，无法被其他
		//进程获取，更无法操作
		if(sem_my < 0 )
			printf("get sem failed... \n");
	}
	else{
		ret = init_semvalue(sem_my,0,1);
	}	
	printf("<>sem is %d\n",semctl(sem_my, 0, GETVAL));
	sleep(7);
	sem_P(sem_my,0);
	printf("<>sem is %d\n",semctl(sem_my, 0, GETVAL));
	printf("Second thing is just do it,........\n");
	sem_V(sem_my,0);
	//del_semvalue(sem_my,0);
	return 0;
}