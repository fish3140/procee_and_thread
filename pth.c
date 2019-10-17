#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
int num =10;
pthread_mutex_t mux;
sem_t sem;
pthread_cond_t pcont;
char sun[10];
/*
void print()
{
	//int i=10;
	//pthread_detach(pthread_self());
	pthread_mutex_lock(&mux);
	while(num>0)
	{
		printf("hell...o___o....num　(%d)........%u\n",num,(unsigned)pthread_self());
		num--;		
	}
	pthread_mutex_unlock(&mux);
}
*/
void printX()
{
	int i=10;
	//pthread_detach(pthread_self());

	for(i=0;i<10;i++)
	{
		sun[i] = i;
		//sem_post(&sem);
		//printf("hell...o___o....num　(%d)........%u\n",num,(unsigned)pthread_self());
		pthread_mutex_lock(&mux);
		pthread_cond_wait(&pcont,&mux);
		pthread_mutex_unlock(&mux);
		printf("hell...o___o....sun　(%d)........%u\n",sun[i],(unsigned)pthread_self());
				
	}

}

void printY()
{
	int i=10;
	//pthread_detach(pthread_self());

	for(i=0;i<10;i++)
	{
		//sem_wait(&sem);
		if(i%3 == 0)
		{
			pthread_mutex_lock(&mux);
			pthread_cond_signal(&pcont);
			pthread_mutex_unlock(&mux);
			sleep(1);
		}
		printf("hell...o___o....sun　(%d)........%u\n",sun[i],(unsigned)pthread_self());
		//num--;		
	}

}

void main()
{
	int err,err1;
	char *name = "thread";
	pthread_t thread1,thread2;
	
	pthread_mutex_init(&mux,NULL);
	sem_init(&sem,0,0);
	pthread_cond_init(&pcont,NULL);
	err = pthread_create(&thread1,NULL,(void *)&printX,"thread");
	err1 = pthread_create(&thread2,NULL,(void *)&printY,"thread1");
	if(err == 0)
	{
		printf("thread create success...\n");
	}
	else
	{
		printf("thread create failed...\n");
	}
	if(err1 == 0)
	{
		printf("thread1 create success...\n");
	}
	else
	{
		printf("thread1 create failed...\n");
	}
	//pthread_detach(thread1);
	//sleep(1);
	err = pthread_join(thread1,NULL);
	if(err==0)
	{
		printf("thread join success...\n");
	}
	else
	{
		printf("thread join failed ...\n");
	}
	err = pthread_join(thread2,NULL);
	if(err==0)
	{
		printf("thread1 join success...\n");
	}
	else
	{
		printf("thread1 join failed ...\n");
	}
	printf("code has ended....\n");
	pthread_mutex_destroy(&mux);
	sem_destroy(&sem);
	pthread_cond_destroy(&pcont);
}

