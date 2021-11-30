#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int main(void)
{
    int pipefds[2];
    int status;
    
    char message[50] = "Hello! This message is from Parent!";
    char message1[50] = "Hy! This message is from Child!";
    char readmessage[50];
    
    status = pipe(pipefds);
    if(status == -1)
    {
        printf("Unable to Create Pipe\n");
        exit(EXIT_FAILURE);
    }
    
    pid_t pid = fork();
    
    if(pid > 0)
    {
        printf("Parent Process : Passing Message to Child...\n");
        write(pipefds[1], message, sizeof(message));
        // wait(NULL);
    }
    else if(pid == 0)
    {
        printf("\nChild Process : \n");
        read(pipefds[0], readmessage, sizeof(readmessage));
        printf("Parent Message : %s\n", readmessage);
        write(pipefds[1], message1, sizeof(message));
        printf("Reading Own message...\n");
        read(pipefds[0], readmessage, sizeof(readmessage));
        printf("Child Message : %s\n", readmessage);
    }
    else
    {
        printf("Unable to Create Child");
    }
    exit(EXIT_SUCCESS);
}