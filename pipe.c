// parent writting , child reading
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>

int main() {

    int fd[2], n;
    char buffer[100];
    pid_t p;

    // Check return value of pipe()
    if (pipe(fd) == -1) {
        perror("Pipe failed");
        exit(1);
    }

    p = fork(); //parent & child created

    if (p < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (p > 0) { // Parent process
        printf("Parent passing value to child\n");

        // Check return value of write()
        if (write(fd[1], "hello\n", 7) == -1) {
            perror("Write to pipe failed");
            exit(1);
        }

        close(fd[1]); // Close the write end after sending the data
    } 
    else { // Child process
        printf("Child printing value received from parent\n");

        // Check return value of read()
        n = read(fd[0], buffer, 100);
        if (n == -1) {
            perror("Read from pipe failed");
            exit(1);
        }

        // Check return value of write()
        if (write(1, buffer, n) == -1) {
            perror("Write to stdout failed");
            exit(1);
        }

        close(fd[0]); // Close the read end after receiving the data
    }

    return 0;
}
