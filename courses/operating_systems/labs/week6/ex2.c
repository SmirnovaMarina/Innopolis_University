#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#define STRING_SIZE 14

int main()
{
    int fd[2];
    int pid;
    char string[STRING_SIZE] = "Hello, world.";
    char string_copy[STRING_SIZE];
    int size_of_read = 0;
    int size_of_write = 0;

    if (pipe(fd) < 0){
        printf("error\n");
        exit(1);
    }
    pid = fork();
    if (pid > 0){
        size_of_write = write(fd[1], string, STRING_SIZE);
        if (size_of_write < STRING_SIZE){
            printf("error\n");
            exit(1);
        }

    }
    else{
        size_of_read = read(fd[0], string_copy, STRING_SIZE);
        if (size_of_read < STRING_SIZE){
            printf("error\n");
            exit(1);
        }
        printf("%s\n", string_copy);
    }

    close(fd[0]);
    close(fd[1]);
    return 0;
}