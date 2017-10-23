#include<sys/types.h>
#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>

int main(void){
	int segment_id;
	char *shared_memory;
	const int size = 4096;
	pid_t pid;

	segment_id = shmget ( IPC_PRIVATE, size, S_IRUSR | S_IWUSR);
	shared_memory = (char *) shmat(segment_id, NULL, 0);
	sprintf(shared_memory, "MESSAGE PASSED!");
	
   	pid=fork();
   	if(pid<0){
		fprintf(stderr,"Fork Failed");
                return 1;
        }
	else if(pid==0){
                execlp("/bin/ls","ls",NULL);

		//Grand Child created
		pid_t gc = fork();
		if (gc<0){
			fprintf(stderr, "\nGrand Child Fork Failed...\n");
			return -1;
		}
		else if (gc == 0){
			execlp("/bin/ls" , "ls", NULL);
		}
		else{
			//Child wait()
			wait(NULL);
			printf("\n%s", shared_memory);
			return 0;
		}

        }
	else{
		//parent wait()
             	wait(NULL);
                printf("\nChild complete\n");
        }

	shmdt(shared_memory);
	shmctl(segment_id, IPC_RMID, NULL);
	
	return 0;
}
