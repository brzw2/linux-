#include<process_copy.h>

int PROCESS_WAIT(){
	pid_t zpid;
	while((zpid=waitpid(-1,NULL,WNOHANG))!=-1){
		if(zpid>0){
		printf("waitpid pid: %d\n",zpid);
		}else{
		}
	}
}
