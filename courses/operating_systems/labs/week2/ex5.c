#include <stdio.h>
#include <math.h>

int height = 0;
int width = 0;
int n = 0;

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

void print_figure1()
{
    for (int i = 1; i<=height; i++)
    {
        for (int j = 1; j<=i; j++)
        {
            printf("*");
        }
        printf("\n");
    }
}

void print_figure2()
{
    int middle = height/2;
    
    for (int i = 1; i<=middle; i++)
    {
        for (int j = 1; j<=i; j++)
        {
            printf("*");
        }
        printf("\n");
    }

    if (height % 2 == 1){
        for (int i = 1; i<=middle+1 ; i++){
            printf("*");
        }
        printf("\n");
    }

    for (int i = middle; i>=1; i--)
    {
        for (int j = i; j>=1; j--)
        {
            printf("*");
        }
        printf("\n");
    }
}

void print_figure3()
{
    for (int i = 1; i<=height; i++)
    {
        for (int j = 1; j<=width; j++)
        {
            printf("*");
        }
        printf("\n");
    }
}

void print_figure_ex3()
{
    int star_count;
    int slash_count;

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
}

void print(int num)
{
    switch (num)
    {
    case 1:
        print_figure1();
        break;
    case 2:
        print_figure2();
        break;
    case 3:
        print_figure3();
        break;
    default:
        print_figure_ex3();
        break;
    }
}

int main(int argc, char *argv[])
{
    int len = length(argv[1]);

    for (int i = len-1; i>=0; i--)
    {
        n = n + pow(10, len-i-1)*((int)argv[1][i] - 48);
    }

    height = n;
    width = 2*n - 1;

    printf("enter number of a figure: \n");
    int num;
    scanf("%d", &num);
    print(num);

    return 0;
}