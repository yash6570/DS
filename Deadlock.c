#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 

pthread_t tid[2];
pthread_mutex_t lock1, lock2; 

/* pthread1 runs here*/
void* func12() 
{ 
    pthread_mutex_lock(&lock1);
    sleep(1);
    pthread_mutex_lock(&lock2);
}

/* pthread2 runs here*/
void* func21() 
{ 
    pthread_mutex_lock(&lock2);
    sleep(1);
    pthread_mutex_lock(&lock1);
    printf("\nDeadlock demonstrated -- never gets printed");
}

int main()
{

    int i = 0; 
    int error; 
    if (pthread_mutex_init(&lock1, NULL) != 0 || pthread_mutex_init(&lock2, NULL) != 0) 
    { 
        printf("\n mutex init has failed\n"); 
        return 1; 
    } 
  
    while (i < 2) 
    { 
        if(i==0)
        {
            error = pthread_create(&(tid[i]), NULL, &func12, NULL); 
            if (error != 0) 
                printf("\nThread can't be created :[%s]", strerror(error)); 
        }
        else
        {
            error = pthread_create(&(tid[i]), NULL, &func21, NULL); 
            if (error != 0) 
                printf("\nThread can't be created :[%s]", strerror(error));
        }
        i++; 
    } 
  
    pthread_join(tid[0], NULL); 
    pthread_join(tid[1], NULL); 
    pthread_mutex_destroy(&lock1); 
    pthread_mutex_destroy(&lock2); 
    return 0;
}
