#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>
#define PID_SIZE 4

int main()
{
    int pid1, pid2;
    int fd[2];
    char pid_str[PID_SIZE] = "";
    char pid_str_copy[PID_SIZE] = "";

    pid1 = fork();
    if (pid1 > 0){
        printf("first fork() was successful\n");

        pid2 = fork();
        if (pid2 > 0){
            printf("second fork() was successful\n");

            int *status;
            int check;

            sprintf(pid_str, "%d", pid2);
            pipe(fd);
            check = write(fd[1], pid_str, PID_SIZE);
            printf("now parent is waiting\n");
            waitpid(pid2, status, WUNTRACED);   
        }
        else{
            while(1);
        }
    }
    else{
        char ch;
        int i = 0;
        int pid_res = 0;
        int len = 0;

        printf("the first child is acting\n");
        sleep(2);
        read(fd[0], pid_str_copy, PID_SIZE);

        len = strlen(pid_str_copy);

        for(i=0; i<len; i++){
            pid_res = pid_res * 10 + ( pid_str_copy[i] - '0' );
        }        
        kill(pid_res, SIGSTOP);      
    }
    while(1);
    return 0;
}