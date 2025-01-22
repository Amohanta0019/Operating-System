#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
int main(){
  pid_t pid;
  pid = fork();
  if(pid == 0){
    printf("Child ID :%d\n", getpid());
    printf("Parent ID :%d\n", getppid());
  }
  else{
    wait(NULL);
    printf("Parent ID :%d\n", getpid());
    printf("Parent's parent ID :%d\n", getppid());
  }
  return 0;
}