#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>  // for sleep()

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0;  // Index to produce into
int out = 0; // Index to consume from

// Semaphores
sem_t empty;  // Counts empty slots
sem_t full;   // Counts filled slots
sem_t mutex;  // Binary semaphore for critical section

void* producer(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        item = rand() % 100;

        sem_wait(&empty);     // Decrease empty count
        sem_wait(&mutex);     // Enter critical section

        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        printf("Produced: %d\n", item);

        sem_post(&mutex);     // Exit critical section
        sem_post(&full);      // Increase full count

        sleep(1);             // Simulate work
    }
    return NULL;
}

void* consumer(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        sem_wait(&full);      // Wait until there's something to consume
        sem_wait(&mutex);     // Enter critical section

        item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        printf("Consumed: %d\n", item);

        sem_post(&mutex);     // Exit critical section
        sem_post(&empty);     // Increase empty count

        sleep(2);             // Simulate work
    }
    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;

    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE); // Initially, all slots are empty
    sem_init(&full, 0, 0);            // No items produced yet
    sem_init(&mutex, 0, 1);           // Binary semaphore = 1

    // Create threads
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // Wait for threads to complete
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // Clean up
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
