#include <stdio.h>

/* Function that perform bubble sort(increasing order) on an array of integers
    Arguments: 
    array - pointer to an array
    len - amount of elements in the array*/
void bubble_sort(int *array, int len)
{
    int buff;

    for (int i = 0; i<len-1; i++){

        for (int j = 0; j<len-1-i; j++){

            if (array[j]>array[j+1]){
                buff = array[j];
                array[j] = array[j+1];
                array[j+1] = buff;
            }
        }

    }
}

int main()
{
    int array[5] = {8, 2, 1, 5, 4};
    bubble_sort(array, 5);
    for (int i = 0; i<5; i++){
        printf("%d ", array[i]);
    }

    return 0;
}