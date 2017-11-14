#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>

int main(void){
   	int pid=fork();
   	
   	if(pid<0){
		fprintf(stderr,"Fork Failed");
                return 1;
    }  
	else if(pid==0){
    		printf("Child Process:");
		execlp("/bin/ls","ls",NULL);
	}	
	else{
		//parent wait()
		wait(NULL);
		printf("In Parent Process, Child complete");
    }
	
	return 0;
}
