#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

void countCharacters(const char *str, int *alpha, int *digit, int *special) {
    *alpha = *digit = *special = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha(str[i])) (*alpha)++;
        else if (isdigit(str[i])) (*digit)++;
        else if (str[i] == '#' || str[i] == '&') (*special)++;
    }
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
        input[strcspn(input, "\n")] = '\0'; // Remove trailing newline
        write(pipefd[1], input, strlen(input) + 1);
        close(pipefd[1]);
    } else { // Child process
        close(pipefd[1]);
        char received[100];
        read(pipefd[0], received, sizeof(received));
        close(pipefd[0]);

        int alpha, digit, special;
        countCharacters(received, &alpha, &digit, &special);
        printf("Child: Alphabets: %d, Digits: %d, Special (#, &): %d\n", alpha, digit, special);
    }

    return 0;
}
