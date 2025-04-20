#include<process_copy.h>

int BLOCK_CUR(const char*src,int pronum){
	int fd=open(src,O_RDWR);
	int fisize=lseek(fd,0,SEEK_END);
	close(fd);
	printf("arrive BLOCK_CUR");
	if(fisize%pronum==0)
		return fisize/pronum;
	return fisize/pronum+1;
}
