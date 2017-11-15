// Producer - Consumer Problem

#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 16

int size=0,x=0, buffer[15], in=0,out=0;

void producer();
void consumer();
int main()
{
    int n;
    printf("\n1.Producer\n2.Consumer\n3.Exit");
    while(1)
    {
        printf("\nEnter your choice:");
        scanf("%d",&n);
        switch(n)
        {
            case 1:    if((size!=MAXSIZE))
                        producer();
                    else
                        printf("Buffer is full!!");
                    break;
            case 2:    if((size>0))
                        consumer();
                    else
                        printf("Buffer is empty!!");
                    break;
            case 3:
                    exit(0);
                    break;
        }
    }
    
    return 0;
}

void producer()
{
    buffer[in] = x++;
    printf("\nProducer produces the item %d",buffer[in]);
    in = (in+1) % MAXSIZE;
    size = size + 1;
}

void consumer()
{
    printf("\nConsumer consumes item %d",buffer[out]);
    out = (out + 1) % MAXSIZE;
    size--;
}
