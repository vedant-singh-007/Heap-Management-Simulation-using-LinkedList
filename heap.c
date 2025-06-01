#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    false,
    true
} bool;

typedef struct MemBlock
{
    int size;
    struct MemBlock *next;
    bool IsFree;
} MemBlock;

MemBlock *head = NULL;
MemBlock *tail = NULL; 

void initialize(int size)
{
    head = (MemBlock *)malloc(sizeof(MemBlock));
    head->size = size;
    head->next = NULL;
    head->IsFree = true;
    tail = head; 
}

MemBlock *allocate(unsigned int size)
{
    MemBlock *temp = head;
    while (temp != NULL)
    {
        if (temp->IsFree == true && temp->size >= size)
        {
            temp->size -= size;

            MemBlock *newBlock = (MemBlock *)malloc(sizeof(MemBlock));
            newBlock->size = size;
            newBlock->next = NULL;
            newBlock->IsFree = false;

            tail->next = newBlock;
            tail = newBlock; 
            return newBlock;
        }
        temp = temp->next;
    }
    printf("No sufficient memory available!\n");
}

void merge(MemBlock *head)
{
    MemBlock *temp = head;
    while (temp != NULL && temp->next != NULL)
    {
        if (temp->IsFree == true && temp->next->IsFree == true)
        {
            temp->size += temp->next->size;
            MemBlock *del = temp->next;
            temp->next = temp->next->next;
            if (del == tail)
            {
                tail = temp; 
            }
            free(del);
            printf("Memory blocks merged!\n");
        }
        else
        {
            temp = temp->next;
        }
    }
}

void free_block(void *p)
{
    MemBlock *temp = head;
    while (temp != NULL)
    {
        if (temp == (MemBlock *)p)
        {
            temp->IsFree = true;
            merge(head);
            return;
        }
        temp = temp->next;
    }
    printf("Invalid free request!\n");
}

void print_memory()
{
    MemBlock *temp = head;
    printf("Memory Blocks:\n");
    while (temp != NULL)
    {
        printf("address %p",temp);
        printf("[Size: %d, Free: %s] -> " , temp->size, temp->IsFree ? "Yes" : "No");

        temp = temp->next;
    }
    printf("NULL\n");
}

int main()
{
    initialize(1024);
    print_memory();

    MemBlock *p = allocate(100);
    print_memory();
    MemBlock *q = allocate(200);
    print_memory();
    MemBlock *r = allocate(300);
    print_memory();

    free_block(p);
    print_memory();
    free_block(r);
    print_memory();
    MemBlock *s = allocate(600);
    
    return 0;
}
