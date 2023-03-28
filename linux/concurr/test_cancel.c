#include<stdio.h>
#include<pthread.h>

void *pt1(void*p)
{	
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);
	int *num=p;
	while(--(*num)>100){
        if(*num==1000)
            printf("block\n");
    }
    
	return NULL;
}
void main(void)
{
	int val=65535;
	pthread_t p1;
	pthread_create(&p1,NULL,pt1,&val);
    pthread_cancel(p1);
	pthread_join(p1,NULL);
	printf("join p1:%d\n",val );
}
