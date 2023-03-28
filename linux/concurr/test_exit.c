#include <stdio.h>
#include <pthread.h>

//线程要执行的函数，arg 用来接收线程传递过来的数据
void *ThreadFun(void *arg)
{
    for(int i=0;i<5;i++){
        printf("%d ",i);
    }
    printf("\n");
    pthread_exit("child thread exit done!\n"); //返回的字符串存储在常量区，并非当前线程的私有资源
    printf("*****************");//此语句不会被线程执行
}

int main()
{
    int res;
    //创建一个空指针
    void * thread_result;
    //定义一个表示线程的变量
    pthread_t myThread;

    res = pthread_create(&myThread, NULL, ThreadFun, NULL);
    if (res != 0) {
        printf("线程创建失败");
        return 0;
    }
    //等待 myThread 线程执行完成，并用 thread_result 指针接收该线程的返回值
    res = pthread_join(myThread, &thread_result);
    if (res != 0) {
        printf("等待线程失败");
    }
    printf("%s", (char*)thread_result);
    return 0;
}