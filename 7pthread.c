// 12. Write program to calculate sum of n numbers using thread library.

//compile using -pthread flag:	gcc -pthread 7pthread.c
#include <stdio.h>	//fprintf(), printf()
#include <pthread.h>// thread library
#include <stdlib.h>	//exit()
int sum = 0;
void *runner(void *param);

int main(int argc, char *argv[]){
	pthread_t tid;
	pthread_attr_t attr;
	
	if(argc < 2){
		fprintf(stderr, "\nEnter Number also...\n");
		exit(0);
	}
	
	if(atoi(argv[1]) < 0){
		fprintf(stderr, "\n%d must be greater than 0...\n", atoi(argv[1]));
		exit(0);
	}
	
	pthread_attr_init(&attr);
	pthread_create(&tid, &attr, runner, argv [1]);
	pthread_join(tid, NULL);
	
	printf("\nSum = %d\n", sum);
}

void *runner(void *param){
	int i, upper = atoi(param);
	
	for(i = 1; i <= upper; i++)
		sum += i;
		
	pthread_exit(0);
}
