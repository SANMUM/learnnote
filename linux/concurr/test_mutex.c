#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 10

int counter = 0;  // 共享资源

pthread_mutex_t mutex;  // 定义互斥锁

void* thread_func(void* arg) {
    int i;
    for (i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex);  // 加锁
        counter++;
        pthread_mutex_unlock(&mutex);  // 解锁
    }
    pthread_exit(NULL);
}

int main() {
    int i;
    pthread_t threads[NUM_THREADS];

    // 初始化互斥锁
    pthread_mutex_init(&mutex, NULL);

    // 创建多个线程并发执行
    for (i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, thread_func, NULL)) {
            printf("Error: pthread_create failed.\n");
            exit(EXIT_FAILURE);
        }
    }

    // 等待所有线程执行完毕
    for (i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL)) {
            printf("Error: pthread_join failed.\n");
            exit(EXIT_FAILURE);
        }
    }

    // 销毁互斥锁
    pthread_mutex_destroy(&mutex);

    printf("Counter value: %d\n", counter);

    return 0;
}
