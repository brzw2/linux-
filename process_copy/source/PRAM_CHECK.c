#include<process_copy.h>


int PRAM_CHECK(const char*srcfile,int pronum,int argc){
printf("PRAM_CHECK ARRIVE \n");
	if(argc<3)
		exit(0);
	if(access(srcfile,F_OK)!=0)
		exit(0);
	if(pronum<5||pronum>100)
		exit(0);
}
