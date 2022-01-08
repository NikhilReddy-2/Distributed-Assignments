#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define MAX 200
int index = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;


void * produce(void * args){
    int * array = (int*)args;
    
    while(index <= MAX){
        pthread_mutex_lock(&lock);
        array[index] = rand()%100;  // Random nums upto 100
        printf("%ld thread wrote - %d\n",pthread_self(),array[index]);
        index++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void * consume(void * args){

    return NULL;
}

int main(int argc, char * argv){

    int arr[MAX];
    pthread_t prod1, prod2;

    pthread_create(&prod1,NULL,produce,&arr);
    pthread_create(&prod2,NULL,produce,&arr);
    
    pthread_join(prod1,NULL);
    pthread_join(prod2,NULL);

    for(int i=0;i<=MAX;i++){
        printf("%d-",arr[i]);
    }
    
    return 0;
}