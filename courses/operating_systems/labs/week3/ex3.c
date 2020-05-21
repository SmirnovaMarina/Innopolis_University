#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int value;
    struct Node *next;
    struct Node *prev;
} node;

node* create_node(int value)
{
    node *new = NULL;
    new = (node*)malloc(sizeof(node));
    new->value = value;
    new->next = NULL;
    new->prev = NULL;
    return new;
}

node* create_list()
{
    node *head = NULL; 
    return head;
}

/* function to insert a new node with value after a given node called predecessor*/
void insert_node(node **predecessor, int value)
{
    node *new = create_node(value);

    if (*predecessor == NULL){ // empty list
        *predecessor = new; // predecessor becomes a head of the list
    }
    else{
        new->next = (*predecessor)->next;
        new->prev = (*predecessor);

        if ((*predecessor)->next != NULL){ // if there is not a single node in the list
            (*predecessor)->next->prev = new;     
        }
        (*predecessor)->next = new;
    }
}

void delete_node(node **head, int value)
{
    node *cur = *head;

    if (cur == NULL){
        printf("empty list\n");
    }
    else{
        while (cur != NULL){
            if (cur->value == value){
                if (cur == *head){ // delete first
                    if (cur->next != NULL){
                        cur->next->prev = NULL;
                        *head = cur->next;
                    }
                    else{ // delete a single element in the list
                        *head = NULL;
                    }    
                }
                else{
                    if (cur->next == NULL){ // delete last
                        cur->prev->next = NULL;
                    }
                    else{
                        cur->prev->next = cur->next;
                        cur->next->prev = cur->prev;
                    }
                }
            }
            cur = cur->next;
        }
    }
}

void print_list(node *head)
{
    node *cur = head;
    if (cur != NULL) { 
        while (cur != NULL){
            printf("value of current node %d\n", cur->value);
            cur = cur->next;
        }
    }
    else{
        printf("empty list\n");
    }
}

int main()
{
    node *head = create_list();
    insert_node(&head, 1);
    insert_node(&head, 2);
    insert_node(&head, 3);
    print_list(head);

    delete_node(&head, 2);
    print_list(head);

    return 0;
}