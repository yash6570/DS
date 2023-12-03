//Purva Gautam
//20184014

#include<stdio.h>
#include<sys/types.h>

int main()
{
        int fd[2];
        pipe(fd);
        printf("Pipe created successfully\n");
        int id = fork();
        int a[3][3];
        int b[3][3];

        if(id < 0)
        {
                printf("Fork failed\n");
                return 0;
        }

        if(id == 0)
        {
                //Child Process
            read(fd[0],a,9*sizeof(int));
            read(fd[0],b,9*sizeof(int));
           
           for(int i=0;i<3;i++)
             for(int j=0;j<3;j++)
                 a[i][j] +=b[i][j];
         
          write(fd[1],a,9*sizeof(int));
          close(fd[1]);

        }
        else
        {
                //Partent 
                printf("Enter 1 matrix\n");
                for(int i=0;i<3;i++)
                   for(int j=0;j<3;j++)
                           scanf("%d",&a[i][j]);
             printf("Enter 2 matrix\n");
                for(int i=0;i<3;i++)
                        for(int j=0;j<3;j++)
                                scanf("%d",&b[i][j]);

              
                write(fd[1] , a , 9*(sizeof(int)));
                sleep(1);
                write(fd[1] , b, 9*sizeof(int));
                close(fd[1]);
                wait(NULL);
                
                read(fd[0] , a, 9*sizeof(int));
               for(int i=0;i<3;i++)
                  {
                   for(int j=0;j<3;j++)
                      printf("%d ",a[i][j]);
                 printf("\n");
                  }
                printf("Exiting Parent process");

        }
        return 0;
}
