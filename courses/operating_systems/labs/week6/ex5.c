#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int pid;
    pid = fork();
    if (pid > 0){
        sleep(2);
        kill(pid, SIGTERM);
    }
    else{
        while(1){printf("I AM ALIVE!\n");}
    }
    return 0;
}