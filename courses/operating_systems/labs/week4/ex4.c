#include <stdio.h>
#include <stdlib.h>
#define true 1
#define MAX_LINE 256

void type_prompt()
{
    printf("> ");
}

void read_command(char *command)
{
    fgets(command, MAX_LINE, stdin);
}

int main(void)
{

    char command[MAX_LINE];

    while (true){
        type_prompt();
        read_command(command);
        system(command);
    }

    return 0;
}