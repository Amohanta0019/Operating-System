#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int matrix[10][10], n;
sem_t sem1, sem2;

void* readMatrix(void* arg) {
    printf("Thread 1: Enter the size of the matrix (n x n): ");
    scanf("%d", &n);
    printf("Thread 1: Enter the matrix elements:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    sem_post(&sem1);
    return NULL;
}

void* checkSymmetry(void* arg) {
    sem_wait(&sem1);
    int symmetric = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] != matrix[j][i]) {
                symmetric = 0;
                break;
            }
        }
    }
    if (symmetric) {
        printf("Thread 2: The matrix is symmetric.\n");
    } else {
        printf("Thread 2: The matrix is not symmetric.\n");
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    sem_init(&sem1, 0, 0);

    pthread_create(&t1, NULL, readMatrix, NULL);
    pthread_create(&t2, NULL, checkSymmetry, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&sem1);

    return 0;
}
