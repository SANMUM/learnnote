#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<assert.h>
volatile long cnt = 0;
void *myfun(void *argv){
    long i;
    long niter = *((long *) argv);
    for(i=0;i<niter;i++){
        cnt++;
    }
}

int main(int argc,char** argv){
    
    long niter;
    pthread_t tid1,tid2;
    if (argc !=2)
    {
        printf("usage:  %s <nithers>\n",argv[0]);
        exit(0);
    }
    niter = atoi(argv[1]);
    int res1 = pthread_create(&tid1,NULL,myfun,&niter);
    int res2 = pthread_create(&tid2,NULL,myfun,&niter);
    assert(res1 == 0);
    assert(res2 == 0);
    int rc = pthread_join(tid1, NULL);
    assert(rc == 0);
    if(cnt == 2*niter){
        printf("ok cnt = %ld\n",cnt);
    }
    else{
        printf("bad cnt=%ld\n",cnt);
    }
    exit(0);
}