#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX 128

typedef struct pt_Entry{
    int virtual_addr;
    unsigned int age : 8; 
    int r : 1; // referenced bit
} Entry;


int main()
{
    int n;
    printf("Enter number of page frames: ");
    scanf("%d", &n);

    Entry *page_table = (Entry *)malloc(n*sizeof(Entry));
    for (int i=0; i<n; i++){
        page_table[i].virtual_addr = -1;
        page_table[i].age = 0;
        page_table[i].r = 0;
    }

    FILE *input = fopen("Lab 09 input.txt","r");
    int va = 0; // virtual address from input
    int i = 0;
    int found = 0;
    int hit_c = 0; // hit counter
    int miss_c = 0; // miss counter
    int clock = 0; // for clock interrupt and R bit update
    int index = -1; // index of found page in page table
    unsigned int min_age = __UINT8_MAX__;
    int min_age_index = 0;

    while (fscanf(input, "%d", &va)!=EOF){
        
        i=0;
        found = 0;
        index = -1;

        // searching for a page in the page table
        while (i<n && found == 0){
            
            if (va == page_table[i].virtual_addr){
                found = 1;
                index = i;
            }
            i++;
        }

        // update age field (shift right) every clock cycle (5 inputs)
        if (clock % 5 == 0) {
            for (i=0; i<n; i++){
                page_table[i].age >> 1;
            }
            clock = 0;
        }

        min_age = __UINT8_MAX__;
        min_age_index = 0;

        // throw away the most unused page with min age
        if (found == 0){
            miss_c++;
            for (i=0; i<n; i++){
                //compare ages with min_age
                if (page_table[i].age < min_age){
                    min_age = page_table[i].age;
                    min_age_index = i;
                }
            }
            page_table[min_age_index].virtual_addr = va;
            page_table[min_age_index].age = MAX;
        }
        else{
            page_table[index].age += MAX;
            hit_c++;
        }
        clock++;
    }

    printf("hit/miss ratio %.3f", (float)hit_c/(float)miss_c);
    fclose(input);

    return 0;
}