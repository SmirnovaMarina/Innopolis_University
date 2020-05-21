#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void *my_realloc(void *ptr, int former_size, int new_size)
{
    if (former_size == 0){
        free(ptr);
        return NULL;
    }

    if (ptr != NULL){
        if (former_size >= new_size){
            return ptr;
        }
        void *new = malloc(new_size);
        if (new == NULL){
            printf("failed to allocate memory\n");
            return NULL;
        }
        memcpy(new, ptr, former_size);
        free(ptr);
        return new;
    }

    
}

int main(){

	printf("Enter original array size:");
	int n1=0;
	scanf("%d",&n1);

	int* array = (int *) calloc(n1, sizeof(int));
	int i;
	for(i=0; i<n1; i++){	
		printf("%d ", array[i]);
	}

	printf("\nEnter new array size: ");
	int n2=0;
	scanf("%d",&n2);
	
    array = (int *) my_realloc(array, n1, n2);

	for(i=0; i<n2;i++){
		printf("%d ", array[i]);
	}
	printf("\n");
	
    free(array);
	return 0;
}
