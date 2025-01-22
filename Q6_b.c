//Write a C program where parent process send a number to child process using PIPE and child process compute whether that number is a prime number or not.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

bool isPrime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

int main() {
    int pipefd[2]; // Array to store pipe descriptors
    pid_t pid;     // Process ID
    int number;

    // Create the pipe
    if (pipe(pipefd) == -1) {
        perror("Pipe creation failed");
        exit(1);
    }

    // Create a child process
    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid > 0) { // Parent process
        close(pipefd[0]); // Close reading end of the pipe

        printf("Parent: Enter a number: ");
        scanf("%d", &number);

        // Write the number to the pipe
        write(pipefd[1], &number, sizeof(number));
        close(pipefd[1]); // Close writing end after sending data
    } else { // Child process
        close(pipefd[1]); // Close writing end of the pipe

        // Read the number from the pipe
        read(pipefd[0], &number, sizeof(number));
        close(pipefd[0]); // Close reading end after receiving data

        // Check if the number is prime
        if (isPrime(number)) {
            printf("Child: The number %d is a prime number.\n", number);
        } else {
            printf("Child: The number %d is not a prime number.\n", number);
        }
    }

    return 0;
}
