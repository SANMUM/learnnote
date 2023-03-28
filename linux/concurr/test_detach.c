#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
void print_message_function( void *ptr );
main ( )
{
          pthread_t thread1;
          pthread_create(&thread1,NULL,(void *)&print_message_function,(void *)0);
          int i;
          for(i=0;i<5;i++)
           {
                printf("%d\n",i);
           }
        // pthread_join(thread1,NULL);
        exit (0) ;
 }
void  print_message_function( void *ptr )
{       
    pthread_detach(pthread_self()); // it 's withdrawn when it's over
    static int g;
    printf("%d\n", g++);

    pthread_exit(0) ;
 }