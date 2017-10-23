#include<sys/types.h>
#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>
int main(void){
	pid_t pid;
	printf("Parent process id: %i \n",(int)getpid());
	/*printf("Entering Parent\n");
	execlp("/bin/ls", "ls", NULL);
	printf("Parent Command executed\n");*/
	pid = fork();
	printf("Child process id: %i \n",(int)pid);
	if(pid < 0){
		fprintf(stderr, "Fork Failed");
	}
	else if (pid == 0) {
		printf("\n(In Else If Block) Child process id: %i",(int)pid);
		printf("\nCurrent process id: %i\n",(int)getpid());
		execlp("/bin/ls", "ls", NULL);
	}
	else{
		wait(NULL);
		printf("\n(In Else Block) Current process id: %i",(int)getpid());
		printf("\nChild Complete\n");
	}
	printf("\nParent Complete\n");
	return 0;
}
