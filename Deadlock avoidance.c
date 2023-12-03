#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h>

pthread_t tid[2]; 
int counter; 
pthread_mutex_t lock2;

/* pthread1 runs here*/
void *func1(void *param)
{  int done = 0;
   while (!done) 
   {
      if (pthread_mutex_trylock(&lock2)) 
      {
         printf("\nWhat's you up to?");

         pthread_mutex_unlock(&lock2);
         done = 1;
      }
   }
   pthread_exit(0);
}

/* pthread2 runs here */
void *func2(void *param)
{  int done = 0;
   while (!done) 
   { 
     if (pthread_mutex_trylock(&lock2)) 
     {
         printf("\nHave a good day!");

         pthread_mutex_unlock(&lock2);
         done = 1;
     }
   }
   pthread_exit(0);
}

int main()
{

    int i = 0; 
    int error; 
    if (pthread_mutex_init(&lock2, NULL) != 0) 
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
    pthread_join(tid[1], NULL); s
    pthread_mutex_destroy(&lock2); 
    return 0;
}
