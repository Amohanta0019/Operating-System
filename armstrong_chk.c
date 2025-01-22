#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int isArmstrong(int num) {
    int sum = 0, temp = num, digits = 0;
    while (temp != 0) {
        digits++;
        temp /= 10;
    }
    temp = num;
    while (temp != 0) {
        sum += pow(temp % 10, digits);
        temp /= 10;
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
        int receivedNumber;
        read(pipefd[0], &receivedNumber, sizeof(receivedNumber));
        close(pipefd[0]);
        if (isArmstrong(receivedNumber)) {
            printf("Child: %d is an Armstrong number.\n", receivedNumber);
        } else {
            printf("Child: %d is not an Armstrong number.\n", receivedNumber);
        }
    }

    return 0;
}
