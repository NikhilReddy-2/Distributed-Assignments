//Has lots of fragmentation and edge cases but works because of simple logic

#include "memoryAlloc.h"
#include<stdio.h>

#define DELTA 64        //
#define MAX_ALLOC_SIZE 1024*1024
node * heap_list_head = NULL;  //Points to the start of free list which keeps metadata about blocks
void * chunk_ptr = NULL;

void * my_alloc(size_t size){
    if(!heap_list_head){
        printf("MemAlloc not initialized.\n");
    }
    node * temp = heap_list_head;
    while(temp){
        if(temp->is_free == true){
            if(temp->size >= size + DELTA ){
                node * new_node = malloc(sizeof(node));
                new_node->size = temp->size - size;
                new_node->ptr = ((char*)temp->ptr)+size;        //Shift the ptr to point to the next free chunk
                new_node->is_free = true;
                new_node->next = temp->next;

                temp->size = size;                              // Allocate size for the new chunk.
                temp->is_free=false;
                temp->next = new_node;

                return temp->ptr;
            }else{
                temp->is_free=false;
                return temp->ptr;
            }
        }
        temp = temp->next;
    }
    //TODO - Get more memory from malloc because our list is out of memory
    printf("Err - Out of memory\n");
    return NULL;
}

void my_dealloc(void * ptr){
    if(!heap_list_head){
        printf("MemAlloc not initialized.\n");
    }
    node * temp = heap_list_head;

    while(temp->ptr != ptr){
        temp = temp->next;
    }
    if(temp){
        temp->is_free=true;             // If the preceding and following memory chunks are free as well, 
                                        // then we should ideally merge them together and make oen huge chunk
    }else{
        printf("Err - Invalid pointer provided.\n");
    }
}

int memory_alloc_init(){
    heap_list_head = (node *)malloc(sizeof(node));
    if(!heap_list_head){
        printf("Err - Out of memory\n");
        return -1;
    }

    heap_list_head->size=MAX_ALLOC_SIZE;
    chunk_ptr=malloc(MAX_ALLOC_SIZE);
    heap_list_head->ptr=chunk_ptr;
    heap_list_head->next=NULL;
    heap_list_head->is_free = true;
}

int memory_alloc_destroy(){
    node * temp = heap_list_head;
    node * next_ptr;

    while(temp){
        next_ptr = temp->next;
        free(temp);
        temp = next_ptr;
    }
    free(chunk_ptr);

    return 0;
}
