#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>

int main(void)
{
    
    pid_t pid = fork();
    
    if(pid>0)
    {
        printf("Parent Process: PID = %d\n", getpid());
        wait(NULL);
    }
    else if(pid == 0)
    {
        sleep(5);
        pid = fork();
        
        if(pid > 0)
        {
            printf("Child Process : PPID = %d, PID = %d\n", getppid(), getpid());
            
            while(1)
                sleep(1);
                
            printf("Child Process : PPID = %d, PID = %d\n", getppid(), getpid());
        }
        else if(pid == 0)
        {
            printf("Child Process : PPID = %d, PID = %d\n",getppid(), getpid());
        }
        else
        {
            printf("Unable to create child process!");
        }
    }
    else
    {
        printf("Unable to create child process!");
    }
    exit(EXIT_SUCCESS);

}