#include <stdlib.h>
#include <stdio.h>

int main()
{
    int N = 0;
    int *array;

    printf("enter N: ");
    scanf("%d", &N);

    array = (int *)calloc(N, sizeof(int));
    for (int i = 0; i<N; i++)
    {
        array[i] = i;
        printf("%d ", array[i]);
    }
    printf("\n");

    free(array);

    return 0;
}