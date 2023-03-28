#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<assert.h>
void *myfun(void *argv);
volatile long cnt = 0;
sem_t mutex;

int main(int argc,char ** argv){
    long niter;
    pthread_t tid1,tid2;
    if(argc != 2){
        printf("usage %s <nither> \n",argv[0]);
        exit(0);
    }
    niter = atoi(argv[1]);
    int res1 = pthread_create(&tid1,NULL,myfun,&niter);
    int res2 = pthread_create(&tid2,NULL,myfun,&niter);
    int sem = sem_init(&mutex,0,1);
    assert(sem >=0 );
    assert(res1 == 0);
    assert(res2 == 0);
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    if(cnt == 2*niter){
        printf("OK! cnt = %ld\n",2*niter);
    }
    else{
        printf("bad! cnt = %ld\n",cnt);
    }

}

void *myfun(void *argv){
    long iter = *((long *) argv);
    for(int i=0;i<iter;i++){
        int wait_value = sem_wait(&mutex);
        assert(wait_value == 0);
        cnt++;
        int post_value = sem_post(&mutex);
        assert(post_value ==0);
    }
    

    return NULL;
}
