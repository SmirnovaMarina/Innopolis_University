#include<stdio.h>
#include <stdlib.h>
#define MAX_LINE 255

int length(char string[])
{
    int len = 0;
    char ch = string[0];
    while (ch != '\0')
    {
        len += 1;
        ch = string[len];
    }
    return len;
}

void inverse(char *string)
{
    int len = length(string);
    int i, j, temp;
    for (int i = 0, j =len-1; i<j; i++, j-- )
    {
        temp = string[i];
        string[i] = string[j];
        string[j] = temp;
    }
}

int main()
{
    char string[MAX_LINE+1] = "";
    char ch;
    int count = 0;

    printf("enter a string of no more than 255 characters\n");
    ch = getc(stdin);
    count++;
    while (ch != EOF && ch != '\n' && count <= MAX_LINE){
        string[count-1] = ch;
        ch = getc(stdin);
        count++;
    }
    string[MAX_LINE] = '\0';

    inverse(string);
    printf("Inversed string: \n");
    printf("%s", string);
    
    return 0;
}