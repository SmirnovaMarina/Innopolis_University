#include <stdio.h>

void swap(int *a, int *b)
{
    int buff;
    buff = *a;
    *a = *b;
    *b = buff;
}

int main()
{
    int a, b;
    int *a_ptr, *b_ptr;
    printf("enter 2 integers: \n");
    scanf("%d %d", &a, &b);
    a_ptr = &a;
    b_ptr = &b;
    swap(a_ptr, b_ptr);
    printf("swapped integers: %d %d\n", a, b);

    return 0;
}