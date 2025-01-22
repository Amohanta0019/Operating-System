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

void generateFibonacci(int n) {
    int a = 0, b = 1, next;
    printf("Fibonacci sequence: ");
    for (int i = 1; i <= n; i++) {
        printf("%d ", a);
        next = a + b;
        a = b;
        b = next;
    }
    printf("\n");
}

int main() {
    pid_t pid;

    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid > 0) { // Parent process
        int n;
        printf("Parent: Enter the range for Fibonacci sequence: ");
        scanf("%d", &n);
        generateFibonacci(n);
    } else { // Child process
        int num;
        printf("Child: Enter a number to check for primality: ");
        scanf("%d", &num);
        if (isPrime(num)) {
            printf("Child: %d is a prime number.\n", num);
        } else {
            printf("Child: %d is not a prime number.\n", num);
        }
    }

    return 0;
}
