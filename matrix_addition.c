#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER;
int r1, c1, r2, c2, a[10][10], b[10][10], c[10][10];

void *matrix_input(){
  pthread_mutex_lock(&mymutex);  // Locking the critical section
  int i, j;

  // Taking input for Matrix A
  printf("Enter rows of matrix A: ");
  scanf("%d", &r1);

  printf("Enter columns of matrix A: ");
  scanf("%d", &c1);

  printf("Enter matrix A:\n");
  for(i = 0; i < r1; i++){
    for(j = 0; j < c1; j++){
      printf("A[%d][%d]: ", i, j);
      scanf("%d", &a[i][j]);
    }
  }

  // Taking input for Matrix B
  printf("Enter rows of matrix B: ");
  scanf("%d", &r2);

  printf("Enter columns of matrix B: ");
  scanf("%d", &c2);

  printf("Enter matrix B:\n");
  for(i = 0; i < r2; i++){
    for(j = 0; j < c2; j++){
      printf("B[%d][%d]: ", i, j);
      scanf("%d", &b[i][j]);
    }
  }

  pthread_mutex_unlock(&mymutex);  // Unlocking the critical section
  return NULL;  // Make sure to return NULL for pthread functions
}

void *add_matrices(){
  pthread_mutex_lock(&mymutex);  // Locking the critical section
  int i, j;

  // Check if addition is possible (same dimensions)
  if(r1 == r2 && c1 == c2){
    // Adding the matrices
    for(i = 0; i < r1; i++){
      for(j = 0; j < c1; j++){
        c[i][j] = a[i][j] + b[i][j];
      }
    }

    // Displaying the result of matrix addition
    printf("Addition of matrices is:\n");
    for(i = 0; i < r1; i++){
      for(j = 0; j < c1; j++){
        printf("%d ", c[i][j]);
      }
      printf("\n");
    }
  }
  else {
    printf("Matrix addition not possible: dimensions do not match.\n");
  }

  pthread_mutex_unlock(&mymutex);  // Unlocking the critical section
  return NULL;  // Make sure to return NULL for pthread functions
}

int main(){
  pthread_t t1, t2;

  // Creating the threads
  pthread_create(&t1, NULL, &matrix_input, NULL);
  pthread_join(t1, NULL); // Waiting for matrix_input to finish before adding

  // Create a thread for matrix addition after the input
  pthread_create(&t2, NULL, &add_matrices, NULL);
  pthread_join(t2, NULL);  // Waiting for add_matrices to finish

  return 0;
}
