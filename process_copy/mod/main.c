#include<process_copy.h>

int main(int argc,char*argv[]){
	int sfd;
	int dfd;
	int pos=atoi(argv[3]);
	int blocksize=atoi(argv[4]);
	if((sfd=open(argv[1],O_RDONLY))==-1){
	perror("oepn srcfile error");
	}
	printf("srcfile %s\n",argv[1]);
	if((dfd=open(argv[2],O_WRONLY|O_CREAT,0755))==-1)
		perror("oepn destfile error");

	printf("destfile %s\n",argv[1]);
	lseek(sfd,pos,SEEK_SET);
	lseek(dfd,pos,SEEK_SET);

	char buf[blocksize];
	bzero(buf,sizeof(buf));
	int len=read(sfd,buf,sizeof(buf));
	write(dfd,buf,len);
	close(dfd);
	close(sfd);
	return 0;
}
