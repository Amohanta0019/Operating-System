//Write a C program that will create a child process by using the fork() system call , then forcefully create a zombie process and display the corresponding process id from process table.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
  pid_t pid = fork();
  if (pid < 0) {
    perror("Fork failed");
    return 1;
  }
  if (pid > 0) { // Parent process
    printf("Parent process ID: %d\n", getpid());
    printf("Zombie process created with PID: %d\n", pid);
    sleep(10); // Keep parent alive to allow observation of the zombie process
  } else { // Child process
    printf("Child process ID: %d\n", getpid());
    printf("Child process exiting.\n");
    exit(0); // Child exits, becomes a zombie
  }
  return 0;
}