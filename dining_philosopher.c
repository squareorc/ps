#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5  // Number of philosophers

sem_t forks[N];       // One semaphore per fork
sem_t room;           // Limit philosophers to N-1 at a time

void* philosopher(void* num) {
    int id = *(int*)num;
    int left = id;
    int right = (id + 1) % N;

    while (1) {
        printf("Philosopher %d is thinking...\n", id);
        sleep(rand() % 3);  // Simulate thinking

        // Try to enter room (max N-1 philosophers at a time)
        sem_wait(&room);

        // Pick up forks (in order to prevent deadlock)
        sem_wait(&forks[left]);
        sem_wait(&forks[right]);

        // Eating
        printf("Philosopher %d is eating...\n", id);
        sleep(rand() % 2 + 1);

        // Put down forks
        sem_post(&forks[right]);
        sem_post(&forks[left]);

        // Leave room
        sem_post(&room);

        printf("Philosopher %d finished eating and left the table.\n", id);
    }

    return NULL;
}

int main() {
    pthread_t philo[N];
    int ids[N];

    // Initialize semaphores
    for (int i = 0; i < N; i++)
        sem_init(&forks[i], 0, 1);

    sem_init(&room, 0, N - 1);  // Allow max N-1 philosophers to prevent deadlock

    // Create threads
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&philo[i], NULL, philosopher, &ids[i]);
    }

    // Let them dine forever (or you can join if needed)
    for (int i = 0; i < N; i++)
        pthread_join(philo[i], NULL);

    // Cleanup (never reached in this case)
    for (int i = 0; i < N; i++)
        sem_destroy(&forks[i]);
    sem_destroy(&room);

    return 0;
}
