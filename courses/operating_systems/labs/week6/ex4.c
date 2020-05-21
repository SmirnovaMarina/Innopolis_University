#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void handler_kill(int sig)
{
    printf("you are going to terminate the program\n");
    exit(1);
}

void handler_stop(int sig)
{
    printf("you are going to stop the program\n");
    sleep(5);
}

void handler_usr1(int sig)
{
    printf("recieved SIGISR1 signal\n");
    printf("exit from the process\n");
    exit(0);
}

int main()
{
    signal(SIGKILL, handler_kill);
    signal(SIGSTOP, handler_stop);
    signal(SIGUSR1, handler_usr1);
    while(1);

    return 0;
}