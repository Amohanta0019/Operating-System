#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int isArmstrong(int num) {
    int original = num, sum = 0, digits = 0;
    while (original > 0) {
        digits++;
        original /= 10;
    }
    original = num;
    while (original > 0) {
        int digit = original % 10;
        sum += pow(digit, digits);
        original /= 10;
    }
    return sum == num;
}

int main() {
    int pipefd[2];
    pid_t pid;
    int number;

    if (pipe(pipefd) == -1) {
        perror("Pipe creation failed");
        exit(1);
    }

    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid > 0) { // Parent process
        close(pipefd[0]);
        printf("Parent: Enter a number: ");
        scanf("%d", &number);
        write(pipefd[1], &number, sizeof(number));
        close(pipefd[1]);
    } else { // Child process
        close(pipefd[1]);
        read(pipefd[0], &number, sizeof(number));
        close(pipefd[0]);
        if (isArmstrong(number)) {
            printf("Child: The number %d is an Armstrong number.\n", number);
        } else {
            printf("Child: The number %d is not an Armstrong number.\n", number);
        }
    }

    return 0;
}
