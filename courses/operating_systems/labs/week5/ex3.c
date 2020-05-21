#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define n 10

int count_items;
pthread_mutex_t mutex;
pthread_cond_t item_available;
pthread_cond_t space_available;

void *producer_f(void *vararg)
{
    int i;
    for (i = 0; i<n; i++)
    {
        pthread_mutex_lock(&mutex);	
        while (count_items == n) pthread_cond_wait(&space_available, &mutex);
        count_items++;
        printf("%d\n", count_items);
        pthread_cond_signal(&item_available);
        pthread_mutex_unlock(&mutex);  
        sleep(2); 
    }
    pthread_exit(NULL);
}

void *consumer_f(void *vararg)
{
    int i;
    for(i = 0; i<n; i++)
    {
        pthread_mutex_lock(&mutex);
        while (count_items == 0) pthread_cond_wait(&item_available, &mutex);
        /* Consume item */
        printf("eat\n");
        count_items--;
        pthread_cond_signal(&space_available);
        pthread_mutex_unlock(&mutex);  
        sleep(1);   
    }
    pthread_exit(NULL);
}	

int main(void)
{
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&item_available, NULL);
    pthread_cond_init(&space_available, NULL);
    count_items = 0;

    pthread_t producer;
    pthread_t consumer;

    pthread_create(&producer, NULL, producer_f, NULL);
    pthread_create(&consumer, NULL, consumer_f, NULL);

    pthread_join(producer, 0);
    pthread_join(consumer, 0);

    pthread_cond_destroy(&space_available);
    pthread_cond_destroy(&item_available);
    pthread_mutex_destroy(&mutex);
    pthread_exit(NULL);
    return 0;
}