#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<sys/wait.h>


int PRAM_CHECK(const char* srcfile,int pronum,int argc);
int BLOCK_CUR(const char*src,int pronum);//任务量计算
int PROCESS_CREATE(const char*src,const char*dest,int blocksize,int pronum);
//多进程创建个重载
int PEOCESS_WAIT(void);//回收僵尸进程
