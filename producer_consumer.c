#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

// Global semaphores and buffer
sem_t empty, full, mutex1;
int buffer[6];
int in = 0, out = 0, item1 = 0;

// Producer function
void *producer(void *arg) {
    while (1) {
        sem_wait(&empty);          // Wait until there is an empty slot
        sem_wait(&mutex1);         // Lock the buffer for exclusive access

        item1++;                   // Produce an item
        printf("Producer produced item %d\n", item1);
        buffer[in] = item1;        // Place the item in the buffer
        in = (in + 1) % 6;         // Circular buffer update

        sem_post(&mutex1);         // Unlock the buffer
        sem_post(&full);           // Signal that a new item is available
        sleep(1);                  // Simulate some delay
    }
}

// Consumer function
void *consumer(void *arg) {
    int item;                      // Declare item inside the function

    while (1) {
        sem_wait(&full);           // Wait until there is a full slot (item available)
        sem_wait(&mutex1);         // Lock the buffer for exclusive access

        item = buffer[out];        // Consume an item from the buffer
        printf("Consumer consumed item %d\n", item);
        out = (out + 1) % 6;       // Circular buffer update

        sem_post(&mutex1);         // Unlock the buffer
        sem_post(&empty);          // Signal that an empty slot is available
        sleep(1);                  // Simulate some delay
    }
}

int main() {
    int p = 3, c = 3;              // Define number of producers and consumers
    pthread_t prod_tid[p], cons_tid[c];  // Arrays to store thread IDs

    // Initialize semaphores
    sem_init(&empty, 0, 6);        // Buffer size is 6 (initially all slots are empty)
    sem_init(&full, 0, 0);         // Initially no items are produced, so full is 0
    sem_init(&mutex1, 0, 1);       // Mutex initialized to 1 (unlocked)

    // Create producer threads
    for (int i = 0; i < p; i++) {
        pthread_create(&prod_tid[i], NULL, producer, NULL);  // Create a producer thread
    }

    // Create consumer threads
    for (int i = 0; i < c; i++) {
        pthread_create(&cons_tid[i], NULL, consumer, NULL);  // Create a consumer thread
    }

    // Wait for all producer threads to finish
    for (int i = 0; i < p; i++) {
        pthread_join(prod_tid[i], NULL);
    }

    // Wait for all consumer threads to finish
    for (int i = 0; i < c; i++) {
        pthread_join(cons_tid[i], NULL);
    }

    // Destroy semaphores (optional, if you want to clean up after threads finish)
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex1);

    return 0;
}
