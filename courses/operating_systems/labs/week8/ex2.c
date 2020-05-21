#include <stdlib.h>
#include <unistd.h>
#define mem_size 10*1024*1024

int main()
{
    int* array;
    int array_size;

    for(int i = 0; i<10; i++)
    {
        array_size = mem_size/(sizeof(int));
        array = (int *) calloc(array_size, sizeof(int));
        sleep(1);
    }

    return 0;
}