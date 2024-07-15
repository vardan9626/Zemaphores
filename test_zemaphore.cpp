#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "semaphore.h"

#define NUM_THREADS 5
#define NUM_ITERATIONS 3

semaphore_t sem;

void* thread_function(void* arg) {
    int thread_id = *(int*)arg;
    
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        sem_wait(&sem);
        printf("Thread %d entered critical section (iteration %d)\n", thread_id, i);
        sleep(1);  // Simulate some work
        printf("Thread %d leaving critical section (iteration %d)\n", thread_id, i);
        sem_post(&sem);
        sleep(1);  // Give other threads a chance
    }
    
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Initialize semaphore with 2 resources
    sem_init(&sem, 2);

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy semaphore
    sem_destroy(&sem);

    return 0;
}
