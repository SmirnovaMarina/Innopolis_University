#include <stdio.h>
#include <math.h>

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

int main(int argc, char *argv[])
{
    int height = 0;
    int width = 0;
    int n = 0;
    int star_count = 0;
    int slash_count = 0;
    int len = length(argv[1]);

    for (int i = len-1; i>=0; i--)
    {
        n = n + pow(10, len-i-1)*((int)argv[1][i] - 48);
    }

    height = n;
    width = 2*n - 1;

    for (int i = 1; i<=height; i++)
    {
        star_count = i*2-1;
        slash_count = (width-star_count)/2;
        for (int j = 0; j<slash_count; j++)
        {
            printf(" ");
        }
        for (int j = 0; j<star_count; j++)
        {
            printf("*");
        }
        for (int j = 0; j<slash_count; j++)
        {
            printf(" ");
        }
        printf("\n");
    }

    return 0;
}