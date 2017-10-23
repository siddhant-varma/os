#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<unistd.h>
int main(void)
{
 const int SIZE=4096;
 const char *name ="OS";
 const char *message_0="message";
 const char *message_1="message passed !";
 int shm_fd;
 char *ptr;
 shm_fd=shm_open(name,O_CREAT|O_RDWR,0666);
 ftruncate(shm_fd,SIZE);
 ptr=mmap(0,SIZE,PROT_WRITE,MAP_SHARED,shm_fd,0);
 printf("\nIn main\n");
 sprintf(ptr,"%s",message_0);
//ptr +=strlen(message_0);
 sprintf(ptr,"%s\n",message_1);
//ptr +=strlen(message_1);
 printf("%s",ptr);
 return 0;
}
