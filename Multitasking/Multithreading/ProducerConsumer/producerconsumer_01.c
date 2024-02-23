/** 
* The producer’s job is to generate data, put it into the buffer, and start again.
* At the same time, the consumer is consuming the data (i.e., removing it from the buffer), one piece at a time.
*
* Problem: Given the common fixed-size buffer, the task is to make sure that the producer can’t add data into the buffer when it is 
* full and the consumer can’t remove data from an empty buffer.
* 
* Solution: The producer is to either go to sleep or discard data if the buffer is full. The next time the consumer removes an item 
* from the buffer, it notifies the producer, who starts to fill the buffer again. In the same manner, the consumer can go to sleep 
* if it finds the buffer to be empty. The next time the producer puts data into the buffer, it wakes up the sleeping consumer.
* 
* Note: An inadequate solution could result in a deadlock where both processes are waiting to be awakened.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count = 0;  // Number of items in the buffer

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_producer = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_consumer = PTHREAD_COND_INITIALIZER;

void *producer(void *arg) {
    for (int i = 0; i < 10; ++i) {
        pthread_mutex_lock(&mutex);

        // Wait if buffer is full
        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&cond_producer, &mutex);
        }

        // Produce an item
        buffer[count++] = i;
        printf("Produced: %d\n", i);

        // Signal consumer that an item is available
        pthread_cond_signal(&cond_consumer);

        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

void *consumer(void *arg) {
    for (int i = 0; i < 10; ++i) {
        pthread_mutex_lock(&mutex);

        // Wait if buffer is empty
        while (count == 0) {
            pthread_cond_wait(&cond_consumer, &mutex);
        }

        // Consume an item
        int item = buffer[--count];
        printf("Consumed: %d\n", item);

        // Signal producer that a space is available
        pthread_cond_signal(&cond_producer);

        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t producer_thread, consumer_thread;

    // Create producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Clean up
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_producer);
    pthread_cond_destroy(&cond_consumer);

    return 0;
}

