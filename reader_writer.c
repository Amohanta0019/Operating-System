#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Semaphores and counters
sem_t mutex, write_lock;
int read_count = 0; // Number of readers currently accessing the shared resource

// Shared resource
int shared_data = 0;

// Reader function
void *reader(void *arg) {
    int reader_id = *((int *)arg);

    while (1) {
        sem_wait(&mutex); // Lock access to modify the reader count
        read_count++;
        if (read_count == 1) {
            sem_wait(&write_lock); // First reader locks the writer
        }
        sem_post(&mutex); // Release the lock

        // Reading the shared resource
        printf("Reader %d is reading the shared data: %d\n", reader_id, shared_data);
        sleep(1); // Simulate reading time

        sem_wait(&mutex); // Lock access to modify the reader count
        read_count--;
        if (read_count == 0) {
            sem_post(&write_lock); // Last reader unlocks the writer
        }
        sem_post(&mutex); // Release the lock

        sleep(1); // Simulate time before reading again
    }
    return NULL;
}

// Writer function
void *writer(void *arg) {
    int writer_id = *((int *)arg);

    while (1) {
        sem_wait(&write_lock); // Lock access for writing

        // Writing to the shared resource
        shared_data++;
        printf("Writer %d is writing the shared data: %d\n", writer_id, shared_data);
        sleep(2); // Simulate writing time

        sem_post(&write_lock); // Release the lock

        sleep(2); // Simulate time before writing again
    }
    return NULL;
}

int main() {
    int num_readers = 3, num_writers = 2;
    pthread_t readers[num_readers], writers[num_writers];
    int reader_ids[num_readers], writer_ids[num_writers];

    // Initialize semaphores
    sem_init(&mutex, 0, 1);      // Binary semaphore for reader count modification
    sem_init(&write_lock, 0, 1); // Binary semaphore for writer access

    // Create reader threads
    for (int i = 0; i < num_readers; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < num_writers; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Wait for threads to finish (infinite loop, so this won't happen)
    for (int i = 0; i < num_readers; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < num_writers; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroy semaphores (not needed in this infinite loop example)
    sem_destroy(&mutex);
    sem_destroy(&write_lock);

    return 0;
}
