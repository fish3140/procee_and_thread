#include <stdio.h>
#include <stdlib.h>
#include<fcntl.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>
#include <errno.h>
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
	  opsptr.sem_flg = SEM_UNDO;
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
	   opsptr.sem_flg = SEM_UNDO;
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
	int shmid;
	char *line = NULL;
	char *p = NULL;
	int sem_my;
	key = ftok("./file", 'a');
	printf("...key is %d ... \n",key);
	if(key < 0 )
		printf("make key value failed...\n");
	shmid = shmget(key, 128, IPC_CREAT|IPC_EXCL|0666);
	if(shmid < 0 )
	{
		printf("share memory buid failed...\n");
		
		if(errno == EEXIST)//文件存在时，直接打开文件获取shmid
        {
            printf("file eexist");
            shmid = shmget(key, 128,0666);
			perror("shmget");
			if(shmid < 0)
			{
				printf("share mem failed again ... \n");
			}
        }
        else
        { 
            perror("shmget fail ");
            exit(1);
        }

	}
	printf("shmid is %d....\n",shmid);
	p = (char *)shmat(shmid, NULL,0);
	perror("shmat");
	if(p == (char *)-1)
	{
		printf("shmat memory  failed...\n");
		exit(1);
	}
	//for semphore start ....
	sem_my = semget(key, 1, IPC_CREAT|IPC_EXCL|0666);
	//创建打开信号量
	if(sem_my < 0 )
	{
		printf("sem create failed  \n");
		sem_my = semget(key, 1, 0666);
		if(sem_my < 0 )
			printf("get sem failed... \n");
		printf("sem create success...  \n");
	}	
	ret = init_semvalue(sem_my,0,1);
	if(ret == -1)
		printf("init failed...\n");
	//end ....
	printf("1.sem is %d\n",semctl(sem_my, 0, GETVAL));
	sleep(5);
	while(1)
	{
		sem_P(sem_my,0);
		read(0,p,5);
		sem_V(sem_my,0);
		if(strstr(p,"end")!= NULL)
			break;
		
	}

	shmdt(p);//解除映射
	shmctl(shmid, IPC_RMID, 0);//删除共享内存
	del_semvalue(sem_my,0);
	return 0;
}