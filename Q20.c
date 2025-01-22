#include <stdio.h>
#include <unistd.h>

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
    int num;
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid > 0) { // Parent process
        printf("Parent: Enter the range for Fibonacci series: ");
        scanf("%d", &num);
        write(STDOUT_FILENO, "Parent is done.\n", 16);
    } else { // Child process
        generateFibonacci(num);
    }

    return 0;
}
