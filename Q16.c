#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

bool isPalindrome(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - i - 1]) return false;
    }
    return true;
}

int main() {
    int pipefd[2];
    pid_t pid;
    char input[100];

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
        printf("Parent: Enter a string: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        write(pipefd[1], input, strlen(input) + 1);
        close(pipefd[1]);
    } else { // Child process
        close(pipefd[1]);
        char received[100];
        read(pipefd[0], received, sizeof(received));
        close(pipefd[0]);
        if (isPalindrome(received)) {
            printf("Child: The string \"%s\" is a palindrome.\n", received);
        } else {
            printf("Child: The string \"%s\" is not a palindrome.\n", received);
        }
    }

    return 0;
}
