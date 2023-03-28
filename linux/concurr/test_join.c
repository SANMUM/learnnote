#include <pthread.h> 
#include <stdio.h> 

 
static int count = 0; 
 
void* thread_run(void* parm) 
{ 
    for (int i=0;i<5;i++) { 
        count++; 
        printf("The thread_run method count is = %d\n",count); 
    } 
    return NULL; 
} 
 
int main() 
{ 
    pthread_t tid; 
    pthread_create(&tid, NULL, thread_run,NULL);
 
    // 加入pthread_join后，主线程"main"会一直等待直到tid这个线程执行完毕自己才结束 
    // 一般项目中需要子线程计算后的值就需要加join方法 
    pthread_join(tid,NULL); 
 
    // 如果没有join方法可以看看打印的顺序 
    printf("The count is = %d\n",count);  
    return 0; 
}