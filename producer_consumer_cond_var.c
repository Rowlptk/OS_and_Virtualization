#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
 
#define SIZE 10
#define NUMB_THREADS 10
#define PRODUCER_LOOPS 2
#define CONSUMER_LOOPS 2
 
#define TRUE 1
#define FALSE 0
 
typedef int buffer_t;
buffer_t buffer[SIZE];
int buffer_index;
 
pthread_mutex_t buffer_lock;
pthread_cond_t full_cond, empty_cond;
 
void insertbuffer(buffer_t value) {
    if (buffer_index < SIZE) {
        buffer[buffer_index++] = value;
    } else {
        printf("Buffer overflow\n");
    }
}
 
buffer_t dequeuebuffer() {
    if (buffer_index > 0) {
        return buffer[--buffer_index];
    } else {
        printf("Buffer underflow\n");
    }
    return 0;
}
 
int isempty() {
    if (buffer_index == 0)
        return TRUE;
    return FALSE;
}
 
int isfull() {
    if (buffer_index == SIZE)
        return TRUE;
    return FALSE;
}
 
void *producer(void *thread_n) {
    int i = 0;
    int value;
    int thread_numb = *(int *)thread_n;
 while (i++ < PRODUCER_LOOPS) {
        sleep(rand() % 10);
        value = rand() % 100;
        pthread_mutex_lock(&buffer_lock);
        
        while (isfull()) {
            pthread_cond_wait(&full_cond, &buffer_lock);
        }
        if (isempty()) {
            insertbuffer(value);
            pthread_cond_signal(&empty_cond);
        } else {
            insertbuffer(value);
        }
        printf("Producer thread %d inserted %d\n", thread_numb, value);
        pthread_mutex_unlock(&buffer_lock);
    }
    pthread_exit(0);
}
 
void *consumer(void *thread_n) {
    int i = 0;
    buffer_t value;
    int thread_numb = *(int *)thread_n;
 
    while (i++ < CONSUMER_LOOPS) {
        pthread_mutex_lock(&buffer_lock);
        while(isempty()) {
            pthread_cond_wait(&empty_cond, &buffer_lock);
        }
        if (isfull()) {
            value = dequeuebuffer();
            pthread_cond_signal(&full_cond);
        } else {
            value = dequeuebuffer();
        }
        printf("Consumer thread %d processed %d\n", thread_numb, value);
        pthread_mutex_unlock(&buffer_lock);
    }
    pthread_exit(0);
}
 
int main() {
 
    buffer_index = 0;
    pthread_t thread[NUMB_THREADS];
    int thread_num[NUMB_THREADS];
    pthread_mutex_init(&buffer_lock, NULL);
    pthread_cond_init(&empty_cond, NULL);
    pthread_cond_init(&full_cond, NULL);
 
    int i = 0;
    for (i = 0; i < NUMB_THREADS; ) {
        thread_num[i] = i;
        pthread_create(&thread[i],NULL,producer,&thread_num[i]);
        i++;
 
        thread_num[i] = i;
        pthread_create(&thread[i],NULL,consumer,&thread_num[i]);
        i++;
    }
    for (i = 0; i < NUMB_THREADS; i++)
        pthread_join(thread[i], NULL);
 
    pthread_mutex_destroy(&buffer_lock);
    pthread_cond_destroy(&full_cond);
    pthread_cond_destroy(&empty_cond);
 
    return 0;
}