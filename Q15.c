#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int a, b, sum;       // Shared variables
sem_t sem1, sem2;    // Semaphores for synchronization

// Thread 1: Reads the first number (a)
void* readA(void* arg) {
    printf("Thread 1: Enter the first number (a): ");
    scanf("%d", &a);
    sem_post(&sem1);  // Signal that 'a' has been read
    return NULL;
}

// Thread 2: Reads the second number (b)
void* readB(void* arg) {
    sem_wait(&sem1);  // Wait until thread 1 finishes reading 'a'
    printf("Thread 2: Enter the second number (b): ");
    scanf("%d", &b);
    sem_post(&sem2);  // Signal that 'b' has been read
    return NULL;
}

// Thread 3: Adds the two numbers (a + b)
void* addAB(void* arg) {
    sem_wait(&sem2);  // Wait until thread 2 finishes reading 'b'
    sum = a + b;
    printf("Thread 3: The sum of %d and %d is %d.\n", a, b, sum);
    return NULL;
}

int main() {
    pthread_t t1, t2, t3;

    // Initialize semaphores
    sem_init(&sem1, 0, 0);  // Initially locked, to wait for thread 1
    sem_init(&sem2, 0, 0);  // Initially locked, to wait for thread 2

    // Create threads
    pthread_create(&t1, NULL, readA, NULL);
    pthread_create(&t2, NULL, readB, NULL);
    pthread_create(&t3, NULL, addAB, NULL);

    // Wait for threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    // Destroy semaphores
    sem_destroy(&sem1);
    sem_destroy(&sem2);

    return 0;
}
