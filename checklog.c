
#include<regex.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/wait.h>
#include<time.h>
#include<signal.h>
#include<pthread.h>
char buffer1[1024];//线程A和B用的那个缓冲区
char buffer2[1024];//线程B和C用的缓冲区
pthread_mutex_t lock1;//锁缓冲区A的锁
pthread_mutex_t lock2;//缓冲区B的锁
pthread_cond_t cond1;
pthread_cond_t cond2;
pthread_cond_t cond3;//分别是三个线程的条件变量
void *t1(void * arg)
{
	FILE *file;
	file=fopen("server.log","r");
	while(1){
	pthread_mutex_lock(&lock1);
	if(buffer1[0]!='\0')
	{
		pthread_cond_wait(&cond1,&lock1);	
	}
	if(fgets(buffer1,sizeof(buffer1),file)==NULL)
	{
		return NULL;	
	}
	printf("t1 success get data from server.log data: %s\n",buffer1);
	pthread_mutex_unlock(&lock1);
	pthread_cond_signal(&cond2);
	}
}

void *t2(void * arg)
{
	while(1){
	pthread_mutex_lock(&lock1);
	while(buffer1[0]=='\0')
	{
		pthread_cond_wait(&cond2,&lock1);	
	}
	char buftmp[1024];
	strcpy(buftmp,buffer1);
	printf("thread t2 got buffer1 data\n");
	pthread_mutex_unlock(&lock1);
	pthread_cond_signal(&cond1);
	char tmp[10]="XTAG";
	if(strncmp(buftmp,tmp,4)==0)
	{
		pthread_mutex_lock(&lock2);
		while(buffer2[0]!='\0')
		{
			pthread_cond_wait(&cond2,&lock2);	
		}
		strcpy(buffer2,buftmp);
		printf("thread t2 put data in buffer2 data:%s\n",buffer2);
		pthread_mutex_unlock(&lock2);
		pthread_cond_signal(&cond3);
	}
	bzero(buffer1,sizeof(buffer1));
	}

}

void * t3(void * arg)
{
	
	FILE *file;
	file=fopen("result.log","a");
	if(file==NULL)
	{
		perror("fopen result.log failed");
		pthread_mutex_unlock(&lock2);
	}
	while(1){
	pthread_mutex_lock(&lock2);
	while(buffer2[0]=='\0')
	{
		pthread_cond_wait(&cond3,&lock2);	
	}
	
	fprintf(file,"%s",buffer2);
	fflush(file);
	printf("thread t3 put data in file data: %s\n",buffer2);
	bzero(buffer2,sizeof(buffer2));
	pthread_mutex_unlock(&lock2);
	pthread_cond_signal(&cond2);
	}
}
int main()
{
	pthread_t tid;
	pthread_mutex_init(&lock1,NULL);
	pthread_mutex_init(&lock2,NULL);

	pthread_cond_init(&cond1,NULL);
	pthread_cond_init(&cond2,NULL);
	pthread_cond_init(&cond3,NULL);
	pthread_create(&tid,NULL,t1,NULL);
	pthread_create(&tid,NULL,t2,NULL);
	pthread_create(&tid,NULL,t3,NULL);
	while(1)
		sleep(1);
}
