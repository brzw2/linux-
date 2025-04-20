#include<process_copy.h>

int main(int argc,char* argv[]){
	int blocksize,pronum;
	if(argv[3]==0)
		pronum=5;
	else 
		pronum=atoi(argv[3]);

	PRAM_CHECK(argv[1],pronum,argc);
	blocksize=BLOCK_CUR(argv[1],pronum);
	PROCESS_CREATE(argv[1],argv[2],blocksize,pronum);
	return 0;
}


