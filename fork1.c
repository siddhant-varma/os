
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
void main()
{
	pid_t pid, p;
	p=getpid();
	pid=fork();

   	if(pid<0){
		fprintf(stderr,"Fork Failed");
    }
    
    printf("\nOutput of fork:\t%d",pid);
    printf("\nProcess id is:\t%d",p);

}

