#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2, pid3;

    printf("Parent Process: PID = %d\n", getpid());

    pid1 = fork(); // First fork creates the first child
    if (pid1 < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid1 == 0) { // First child process
        printf("Child 1: PID = %d, Parent PID = %d\n", getpid(), getppid());
        pid2 = fork(); // Second fork within Child 1 creates a grandchild
        if (pid2 < 0) {
            perror("Fork failed");
            return 1;
        }
        if (pid2 == 0) {
            printf("Grandchild 1: PID = %d, Parent PID = %d\n", getpid(), getppid());
        } else {
            wait(NULL); // Wait for Grandchild 1 to finish
        }
    } else { // Parent process
        pid3 = fork(); // Second fork in the parent creates the second child
        if (pid3 < 0) {
            perror("Fork failed");
            return 1;
        }
        if (pid3 == 0) { // Second child process
            printf("Child 2: PID = %d, Parent PID = %d\n", getpid(), getppid());
        } else {
            wait(NULL); // Wait for Child 1 to finish
            wait(NULL); // Wait for Child 2 to finish
        }
    }

    return 0;
}
/*
Parent Process: PID = 12345
Child 1: PID = 12346, Parent PID = 12345
Grandchild 1: PID = 12347, Parent PID = 12346
Child 2: PID = 12348, Parent PID = 12345


Parent (PID = 12345)
├── Child 1 (PID = 12346)
│   └── Grandchild 1 (PID = 12347)
└── Child 2 (PID = 12348)


*/