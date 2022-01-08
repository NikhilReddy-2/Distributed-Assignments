#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

#define MAX 200
int p_index = 0;
int c_index = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
sem_t mutex;


void * produce(void * args){
    int * array = (int*)args;
    
    while(p_index <= MAX){
        pthread_mutex_lock(&lock);
        array[p_index] = rand()%100;  // Random nums upto 100
        printf("%ld Produced - %d\n",pthread_self(),array[p_index]);
        p_index++;
        sem_post(&mutex);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void * consume(void * args){
    int * array = (int*)args;
    int temp;

    while(c_index<=MAX){
        sem_wait(&mutex);
        pthread_mutex_lock(&lock);
        temp = array[c_index];
        array[c_index] = -1;
        printf("%ld Consumed - %d\n",pthread_self(),temp);
        c_index++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main(int argc, char * argv){

    int arr[MAX];
    sem_init(&mutex,0,0);
    pthread_t prod1, prod2, consumer;

    pthread_create(&prod1,NULL,produce,&arr);
    pthread_create(&prod2,NULL,produce,&arr);
    pthread_create(&consumer,NULL,consume,&arr);
    
    pthread_join(prod1,NULL);
    pthread_join(prod2,NULL);
    pthread_join(consumer,NULL);

    sem_destroy(&mutex);


    for(int i=0;i<=MAX;i++){
        printf("%d-",arr[i]);
    }
    
    return 0;
}