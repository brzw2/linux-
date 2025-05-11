
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

int blocksize;
int sfd;
int dfd;
int check_pram(int argc,int thread_num,char * src_file)
{
	if(argc<3)
	{
		printf("pram number error\n");
		exit(0);
	}
	if(thread_num<5||thread_num>381)
	{
		printf("thread_num failed\n");
	}
	if((access(src_file,F_OK))!=0)
	{
		printf("file not exist\n");
		exit(0);
	}
	return 0;
}

int block_cur(char * src_file,int thread_num)
{
	int fd=open(src_file,O_RDWR);
	int size=lseek(fd,0,SEEK_END);
	close(fd);
	if(size%thread_num==0)
		return size/thread_num;
	return size/thread_num+1;
}
void * thread_copy(void * arg);
int thread_create(int thread_num)
{
	int i;
	int t=0;
	pthread_t tidarr[400];
	for(i;i<thread_num;i++)
	{
		int err;
		pthread_t tid;
		int tmp=i;
		if((err=pthread_create(&tid,NULL,thread_copy,(void *)&tmp))>0)
		{
			printf("create thread failed %s\n",strerror(err));
			exit(0);
		}
		tidarr[t++]=tid;
	}

	for(int i=0;i<t;i++)
	{
		pthread_join(tidarr[i],NULL);	
	}
}

void * thread_copy(void * arg)
{
	//src,dest,blocksize,pos(拷贝偏移量)
	int pos=(int)arg*blocksize;
	lseek(sfd,pos,SEEK_SET);
	lseek(dfd,pos,SEEK_SET);
	char buf[1024];
	bzero(buf,sizeof(buf));
	int len=read(sfd,buf,sizeof(buf));
	write(dfd,buf,len);
}
int main(int argc,char *argv[])
{
	int thread_num;
	if(argv[3]==0)
		thread_num=5;
	else
		thread_num=atoi(argv[3]);
	check_pram(argc,thread_num,argv[1]);
	blocksize=block_cur(argv[1],thread_num);
	//打开源文件 创建目标文件
	sfd=open(argv[1],O_RDONLY);
	dfd=open(argv[2],O_WRONLY|O_CREAT,0664);
	thread_create(thread_num);
	return 0;	
}
