#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int main(void)
{
    char *command = "ls";
    char *args[] = {command, "-l", NULL};

    pid_t pid = fork();
    
    if(pid == 0)
    {
        
        printf("\nChild Process\n");
        printf("Child PPID = %d, PID = %d\n",getppid(), getpid());
        int status = execvp(command, args);
        if(status == -1)
        {
            printf("Invalid Command!\n");
        }
        exit(EXIT_SUCCESS);
    }
    else if(pid > 0)
    {
        printf("Parent Process\n");
        printf("Parent PID : %d, PPID = %d\n", getpid(), getppid());
        printf("Waiting for child process to finish.\n");
        wait(NULL);
        printf("\nChild process finished.\n");
    }
    else
    {
        printf("Unable to create child process.");
        exit(EXIT_FAILURE);
    }
}