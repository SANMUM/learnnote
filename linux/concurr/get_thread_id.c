#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<pthread.h>

void* fun(void *arg)
{
    printf("子线程id:%lu\n",pthread_self());
    return NULL;
}

int main()
{
    pthread_t pthid;
    int res = pthread_create(&pthid,NULL,fun,NULL);
    if(res != 0)
    {
        printf("%s\n",strerror(res));
    }
    printf("主线程id:%lu\n",pthread_self());
    sleep(1);
    return 0;
}