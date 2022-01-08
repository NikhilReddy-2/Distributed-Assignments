#ifndef MEMORY_ALLOC
#define MEMORY_ALLOC
#include<stdlib.h>
#include<stdbool.h>


typedef struct list_node{
    size_t size;
    bool is_free;
    void * ptr;
    struct list_node * next;
}node;

void * my_alloc(size_t size);

void my_dealloc(void * ptr);

int memory_alloc_init();

#endif