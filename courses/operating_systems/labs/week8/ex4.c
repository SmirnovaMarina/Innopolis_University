#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/resource.h>
#define mem_size 10*1024*1024

int main()
{
    int* array;
    int array_size;
    struct rusage data;

    for(int i = 0; i<10; i++)
    {
        array_size = mem_size/(sizeof(int));
        array = (int *) calloc(array_size, sizeof(int));
        getrusage(RUSAGE_SELF, &data);
        printf("Memory used %li\n",data.ru_maxrss);
        sleep(1);
    }

    return 0;
}