#include"stdio.h"
void main()
{
    int lmem,psize,pmem,i,j,k,c[10],str;
    int a[20],b[35],ch,page,index,abs,frame;
    printf("\n enter page size::");
    scanf("%d",&psize);
    printf("\nenter logical memory size::");
    scanf("%d",&lmem);
    printf("\n%d",lmem);
    printf("\nenter phisical memory size::");
    scanf("%d",&pmem);
    printf("\n enter data::");
    for(i=0;i<lmem;i++)
        scanf("%d",&a[i]);
    for(i=0;i<32;i++)
        b[i]=-1;
    for(i=0;i<lmem/psize;i++)
    {
        printf("\nenter starting location for page::%d",i);
        scanf("%d",&str);
        if(str%psize==0)
        {

            c[i]=str/psize;
            for(j=str,k=i*4;j<j+psize,k<i*4+psize;j++,k++)
            {
            b[j]=a[k];
            }
        }
        else
            printf("\n wrong entry for page the page address shud be multiples of 4");
    }
    printf("\n the page table is::");
    printf("\n page \t\t frame");

    for(i=0;i<lmem/psize;i++)
        printf("\n %d\t %d",i,c[i]);
    printf("\n enter for which data the mapping address to be found::");
    scanf("%d",&ch);
    for(i=0;i<lmem;i++)
    {
        if(ch==a[i])
        {
            index=i;
            page=index/4;
            frame=c[page];
            abs=(frame*psize)+(index%psize);
        }

    }

    printf("\n the physical address for %d is::%d",ch,abs);
}
