#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

void countVowelsConsonants(char* str, int* vowels, int* consonants) {
    *vowels = *consonants = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha(str[i])) {
            char lower = tolower(str[i]);
            if (lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u') {
                (*vowels)++;
            } else {
                (*consonants)++;
            }
        }
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
        input[strcspn(input, "\n")] = '\0';
        write(pipefd[1], input, strlen(input) + 1);
        close(pipefd[1]);
    } else { // Child process
        close(pipefd[1]);
        char received[100];
        int vowels, consonants;
        read(pipefd[0], received, sizeof(received));
        close(pipefd[0]);
        countVowelsConsonants(received, &vowels, &consonants);
        printf("Child: Vowels: %d, Consonants: %d\n", vowels, consonants);
    }

    return 0;
}
