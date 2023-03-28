#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

#define BUFFER_SIZE 10

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

void* producer(void* arg) {
    int item = 1;
    while (item<20) {
        sem_wait(&empty);  // 等待空缓冲区
        pthread_mutex_lock(&mutex);
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        printf("Producer: Produced item %d\n", item++);
        pthread_mutex_unlock(&mutex);
        sem_post(&full);  // 发送满缓冲区信号
    }
    exit(0);
    return NULL;
}

void* consumer(void* arg) {
    int item;
    while (1) {
        sem_wait(&full);  // 等待满缓冲区
        pthread_mutex_lock(&mutex);
        item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        printf("Consumer: Consumed item %d\n", item);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);  // 发送空缓冲区信号
    }
    return NULL;
}

int main() {
    sem_init(&empty, 0, BUFFER_SIZE);  // 初始化空缓冲区信号量
    sem_init(&full, 0, 0);  // 初始化满缓冲区信号量
    pthread_mutex_init(&mutex, NULL);  // 初始化互斥锁

    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    sem_destroy(&empty);  // 销毁信号量
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);  // 销毁互斥锁
    return 0;
}
