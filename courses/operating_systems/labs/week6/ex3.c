#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void handler(int sig)
{
    int yes = 0;
    printf("Are you sure? 1-yes 0-no\n");
    scanf("%d", &yes);
    if (yes == 1){
        exit(1);
    }
}

int main(void)
{
    printf("Hello!\n");
    signal(SIGINT, handler);
    while (1);
    
    return 0;
}