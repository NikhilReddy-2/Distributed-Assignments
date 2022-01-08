//Fragmentation

#include "memoryAlloc.h"
#include<stdio.h>
#define MAX_ALLOC_SIZE 1024*1024
node * free_list_head;  //Points to the start of free list which keeps metadata about blocks

void * my_alloc(size_t size){

}

void my_dealloc(void * ptr){

}

int memory_alloc_init(){
    free_list_head = (node *)malloc(sizeof(node));
    if(!free_list_head){
        printf("Err - Out of memory\n");
        exit(-1);
    }

    free_list_head->size=MAX_ALLOC_SIZE;
    free_list_head->ptr=malloc(MAX_ALLOC_SIZE);
    free_list_head->next=NULL;
    free_list_head->is_free = true;
}
