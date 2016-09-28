/*
|---------------------------------------------------------|
|Authors:  Kalfarentzos Konstantinos Georgios A.M.: 2444  |
|          Karanikolas Nikolaos               A.M.: 2449  |
|---------------------------------------------------------|

This is a simple demonstration for didactic purposes of the use of 
POSIX threads and safeguarding the exclusive access to a shared global 
variable with Mutex. 
The program evaluates the sum of N integers, where N is argv[1]. To do so
it creates N threads, each of which is responsible to increment the global 
variable sum by one of the summands.

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h> 
#include <pthread.h>
#include "ex1.h"

int main(int argc, char *argv[]){
    int N = atoi(argv[1]);
    pthread_t * Thread = (pthread_t *)malloc(N * sizeof(pthread_t));

    struct timeval Start, Stop, Diff;
    int i;

    gettimeofday(&Start, NULL);
    fprintf(stdout, "Thread 0. PID:%d, TID:%ld.\n", getpid(), pthread_self());
    fprintf(stdout,"Thread 0. Create threads.\n");

    for (i=0; i<N; i++)
        if (pthread_create(&Thread[i], NULL, WorkFunction, (void*)i))
            fprintf(stderr,"Thread creation failed.\n");
    
    for (i=0; i<N; i++)
        if (pthread_join(Thread[i], NULL))
            fprintf(stderr,"join thread failed.\n");


    fprintf(stdout,"Thread 0. Exits.\n");
    printf("Sum = %d\n", Sum);
    gettimeofday(&Stop, NULL);
    timersub(&Stop, &Start, &Diff);
    fprintf(stdout,"Time: %ld.%ld usec\n", Diff.tv_sec, Diff.tv_usec);
    free(Thread);
    return 0;
}

void* WorkFunction(void* Arg){
    pthread_mutex_lock(&Mutex);
    Sum += (int) Arg;
    pthread_mutex_unlock(&Mutex); 
    return NULL;
}
