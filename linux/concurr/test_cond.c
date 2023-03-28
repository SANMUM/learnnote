#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int counter = 0;

void* thread1(void* arg) {
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex);
        counter++;
        printf("Thread 1: Counter = %d\n", counter);
        pthread_cond_signal(&cond); // will lock thread 2
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* thread2(void* arg) {
    pthread_mutex_lock(&mutex);
    while (counter < 5) {
        printf("Thread 2: Waiting for counter to be greater than or equal to 5\n");
        pthread_cond_wait(&cond, &mutex); // will unlock thread2
    }
    printf("Thread 2: Counter has reached %d, continuing execution\n", counter);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}
