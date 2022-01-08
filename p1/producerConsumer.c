#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

#define MAX_ELEMENTS 1000
int p_index = 0;        // Used by producer threads to index the array
int c_index = 0;        // Used by the consumer thread(s) to index the array. (could be made local)
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
sem_t items_available;  // Used to signal if and item is available to be consumed
sem_t slots_available;  // Used to signal if a slot is available to produce

/*
Producer:
    Writes randomly generated numbers to an array. Locks are acquired when 
    a thread has to write to the array.
*/
void * produce(void * args){
    int * array = (int*)args;
    if(!array){
        printf("Producer got NULL pointer\n");
        exit(-1);
    }
    
    while(1){
        sem_wait(&slots_available);     // If available then start producing
        pthread_mutex_lock(&lock);
        
        p_index = (p_index+1)%MAX_ELEMENTS;
        
        array[p_index] = rand()%100;
        printf("%ld Produced - %d\n",pthread_self(),array[p_index]);
        sem_post(&items_available);     // Inform consumer to start consuming
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}


/*
Consumer:
    Consumes i.e. Changes positive integer produced by the producer too '-1'.
*/
void * consume(void * args){
    int * array = (int*)args;
    if(!array){
        printf("Consumer got NULL pointer\n");
        exit(-1);
    }
    int temp;

    while(1){
        c_index = (c_index+1)%MAX_ELEMENTS;
        printf("%ld is waiting for items\n",pthread_self());
        sem_wait(&items_available);     // Waiting for items to be produced
        pthread_mutex_lock(&lock);
        temp = array[c_index];
        array[c_index] = -1;
        sem_post(&slots_available);     // Inform producer to start producing
        printf("%ld Consumed - %d\n",pthread_self(),temp);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main(int argc, char * argv){

    int arr[MAX_ELEMENTS];

    for(int i=0;i<=MAX_ELEMENTS;i++){
        arr[i] = -1;        // Initialize to -1
    }

    sem_init(&items_available,0,0);
    sem_init(&slots_available,0,MAX_ELEMENTS);
    pthread_t prod1, prod2, consumer;

    pthread_create(&prod1,NULL,produce,&arr);
    pthread_create(&prod2,NULL,produce,&arr);
    pthread_create(&consumer,NULL,consume,&arr);
    
    pthread_join(prod1,NULL);
    pthread_join(prod2,NULL);
    pthread_join(consumer,NULL);

    sem_destroy(&items_available);

    
    return 0;
}