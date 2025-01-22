//Write a C program where the parent process sends a number to child process using PIPE and child process computes whether that number is an odd or even number.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

        // Check if the number is odd or even
        if (number % 2 == 0) {
            printf("Child: The number %d is an even number.\n", number);
        } else {
            printf("Child: The number %d is an odd number.\n", number);
        }
    }

    return 0;
}
