#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
  
pthread_t tid[3]; 
int counter; 
pthread_mutex_t lock; 
  
void* trythis(void* arg) 
{ 
    pthread_mutex_lock(&lock); 
    if(arg==0)
    {
        FILE *fptr=fopen("chk.txt","w");
        fputs("Hello, Kerman! ** ",fptr);
        fclose(fptr);
        printf("Write performed\n");
    }
    else if(arg==1)
    {
        char str[50];
        FILE *fptr=fopen("chk.txt","r");
        fgets(str,50,fptr);
        fclose(fptr);
        printf("Read performed\nStatement: %s",str);
    }
    else if(arg==2)
    {
        char str[50];
        FILE *fptr=fopen("chk.txt","a");
        fputs("Hello, Gene Kerman!\n",fptr);
        printf("Update performed\n");
        fclose(fptr);
        FILE *fptr1=fopen("chk.txt","r");
        fgets(str,50,fptr1);
        printf("Updated material: %s",str);
        fclose(fptr);
    }
  
    pthread_mutex_unlock(&lock); 
  
    return NULL; 
} 
  
int main(void) 
{ 
    int i = 0; 
    int error; 
  
    if (pthread_mutex_init(&lock, NULL) != 0) 
    { 
        printf("\n mutex init has failed\n"); 
        return 1; 
    } 
  
    while (i < 3) 
    { 
        error = pthread_create(&(tid[i]), NULL, &trythis, (void *)i); 
        if (error != 0) 
            printf("\nThread can't be created :[%s]", strerror(error)); 
        i++; 
    } 
  
    pthread_join(tid[0], NULL); 
    pthread_join(tid[1], NULL); 
    pthread_join(tid[2], NULL); 
    pthread_mutex_destroy(&lock); 
  
    return 0; 
} 

