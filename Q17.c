#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid > 0) {
        printf("Parent: My PID is %d, Child's PID is %d\n", getpid(), pid);
    } else {
        printf("Child: My PID is %d, Parent's PID is %d\n", getpid(), getppid());
    }

    return 0;
}
