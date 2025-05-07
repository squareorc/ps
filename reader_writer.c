#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int read_count = 0;

sem_t rw_mutex;         // Allows writers exclusive access
sem_t read_count_mutex; // Protects read_count
sem_t queue_mutex;      // Fairness semaphore (queue lock)

void* reader(void* arg) {
    int id = *((int*)arg);

    // Fairness: wait in line (so writers aren’t starved)
    sem_wait(&queue_mutex);
    sem_wait(&read_count_mutex);
    read_count++;
    if (read_count == 1)
        sem_wait(&rw_mutex); // First reader blocks writers
    sem_post(&read_count_mutex);
    sem_post(&queue_mutex);

    // Critical section: Reading
    printf("Reader %d is reading...\n", id);
    sleep(1);

    // Exit section
    sem_wait(&read_count_mutex);
    read_count--;
    if (read_count == 0)
        sem_post(&rw_mutex); // Last reader allows writer
    sem_post(&read_count_mutex);

    printf("Reader %d finished reading.\n", id);
    return NULL;
}

void* writer(void* arg) {
    int id = *((int*)arg);

    // Fairness: wait in line like readers
    sem_wait(&queue_mutex);
    sem_wait(&rw_mutex);  // Get exclusive access
    sem_post(&queue_mutex);

    // Critical section: Writing
    printf("Writer %d is writing...\n", id);
    sleep(2);

    // Exit section
    sem_post(&rw_mutex);
    printf("Writer %d finished writing.\n", id);
    return NULL;
}

int main() {
    pthread_t r[5], w[2];
    int ids[5] = {1, 2, 3, 4, 5};

    // Initialize semaphores
    sem_init(&rw_mutex, 0, 1);
    sem_init(&read_count_mutex, 0, 1);
    sem_init(&queue_mutex, 0, 1);

    // Spawn writer threads
    for (int i = 0; i < 2; i++)
        pthread_create(&w[i], NULL, writer, &ids[i]);

    // Spawn reader threads
    for (int i = 0; i < 5; i++)
        pthread_create(&r[i], NULL, reader, &ids[i]);

    // Join threads
    for (int i = 0; i < 2; i++)
        pthread_join(w[i], NULL);
    for (int i = 0; i < 5; i++)
        pthread_join(r[i], NULL);

    // Cleanup
    sem_destroy(&rw_mutex);
    sem_destroy(&read_count_mutex);
    sem_destroy(&queue_mutex);

    return 0;
}
