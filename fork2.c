#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void main()
{
	pid_t pid;
	pid=fork();
	if(pid<0){
		fprintf(stderr,"Fork Failed");
        exit(1);
    }
    if(pid==0){
    	//printf("\nChild Process:");
		execlp("/bin/ls","ls",NULL);
	}	
	else{
		printf("\nParent Process.\n");
    }
    exit(1);
		
}
