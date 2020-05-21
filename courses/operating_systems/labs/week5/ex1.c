#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NUM_THREADS 5

pthread_t thread_array[NUM_THREADS];
int thread_id[NUM_THREADS];

void* print(void* arg)
{
    int *ptr = arg;
    int value = *ptr;
    
    printf("Hello World from thread %d - I was created in iteration %d !\n", (int) pthread_self(), value);
    thread_id[value] = (int)pthread_self();
    pthread_exit(NULL);
}

int main(int argc, char * argv[]) 
{
    int code = 0;
    int i = 0;

    for (i = 0; i < NUM_THREADS; i++) 
    {
        code = pthread_create(&thread_array[i], NULL, (void *)print, (void *)(&i));
        if (code == -1) {
            printf("\n ERROR");
            exit(1);
        }
        sleep(1);
        printf("I am thread %d. Create new thread %d in iteration %d\n", (int) pthread_self(), thread_id[i], i);
    }

    pthread_exit(NULL);
    return 0;
}