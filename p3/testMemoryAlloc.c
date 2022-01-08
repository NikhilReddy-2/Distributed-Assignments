#include "memoryAlloc.h"
#include<stdio.h>

#define TEST_WORKS 1024

int main()
{

    int ret = memory_alloc_init();
    int * arr = my_alloc(TEST_WORKS);
    if(!arr){
        printf("mem not available");
        exit(-1);
    }
    my_dealloc(arr);

    ret = memory_alloc_destroy();

    return 0;
}