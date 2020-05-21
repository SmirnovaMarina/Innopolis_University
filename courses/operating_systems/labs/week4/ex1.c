#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int n =((int) *(argv[1]))-48;
    int pid = fork();

    if (pid > 0){
        printf("Hello from parent [%d-%d]\n", pid, n);
    }
    else{
        if (pid==0){
            printf("Hello from child [%d-%d]\n", pid, n);
        }
        else{
            printf("failed to create a process\n");
        }
    }
    
    return 0;
}