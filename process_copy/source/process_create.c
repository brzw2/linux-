#include<process_copy.h>

int PROCESS_CREATE(const char*src,const char*dest,int blocksize,int pronum){
	pid_t pid;
	int i=0;
	printf("arrive process_create");
	for(i;i<pronum;i++)
	{
		pid=fork();
		if(pid==0)
			break;
	}
	if(pid>0){
		PROCESS_WAIT();//非阻塞循环回收	
	}else if(pid==0){
		printf("arrive process_create copy\n");
		int pos;
		pos=blocksize*i;
		char strpos[10];
		char strblocksize[10];
		sprintf(strpos,"%d",pos);
		sprintf(strblocksize,"%d",blocksize);
		execl("/home/colin/20240720/process/process_copy/mod/copy",src,dest,strpos,strblocksize,NULL);
		perror("execl error");
	}else
	{
	perror("fork call failed");
	exit(0);	
	}
return 0;	
}
