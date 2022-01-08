//Fragmentation

#include "memoryAlloc.h"
#include<stdio.h>

#define DELTA 64        //
#define MAX_ALLOC_SIZE 1024*1024
node * heap_list_head;  //Points to the start of free list which keeps metadata about blocks

void * my_alloc(size_t size){
    node * temp = heap_list_head;
    while(temp){
        if(temp->is_free == true){
            if(temp->size > size + DELTA ){
                node * new_node = malloc(sizeof(node));
                new_node->size = temp->size - size;
                new_node->ptr = ((char*)temp->ptr)+size;        //Shift the ptr to point to the next free chunk
                new_node->is_free = true;
                new_node->next = temp->next;

                temp->size = size;                              //
                temp->is_free=false;
                temp->next = new_node;

                return temp->ptr;
            }else{
                temp->is_free=false;
                return temp->ptr;
            }
        }
    }
    // Get more memory from malloc because our list is out of memory
}

void my_dealloc(void * ptr){

}

int memory_alloc_init(){
    heap_list_head = (node *)malloc(sizeof(node));
    if(!heap_list_head){
        printf("Err - Out of memory\n");
        exit(-1);
    }

    heap_list_head->size=MAX_ALLOC_SIZE;
    heap_list_head->ptr=malloc(MAX_ALLOC_SIZE);
    heap_list_head->next=NULL;
    heap_list_head->is_free = true;
}
