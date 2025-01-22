#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int a, b, sum;
sem_t sem1, sem2;

void* readA(void* arg) {
    printf("Thread 1: Enter value for a: ");
    scanf("%d", &a);
    sem_post(&sem1); // Signal sem1
    return NULL;
}

void* readB(void* arg) {
    sem_wait(&sem1); // Wait for sem1
    printf("Thread 2: Enter value for b: ");
    scanf("%d", &b);
    sem_post(&sem2); // Signal sem2
    return NULL;
}

void* add(void* arg) {
    sem_wait(&sem2); // Wait for sem2
    sum = a + b;
    printf("Thread 3: The sum of a and b is %d\n", sum);
    return NULL;
}

int main() {
    pthread_t t1, t2, t3;
    sem_init(&sem1, 0, 0);
    sem_init(&sem2, 0, 0);

    pthread_create(&t1, NULL, readA, NULL);
    pthread_create(&t2, NULL, readB, NULL);
    pthread_create(&t3, NULL, add, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    sem_destroy(&sem1);
    sem_destroy(&sem2);

    return 0;
}
