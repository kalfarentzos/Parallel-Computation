/*
|---------------------------------------------------------|
|Authors:  Kalfarentzos Konstantinos Georgios A.M.: 2444  |
|          Karanikolas Nikolaos               A.M.: 2449  |
|---------------------------------------------------------|

This is a simple demonstration for didactic purposes of the use of 
POSIX threads and safeguarding the exclusive access to a shared global 
variable with Mutex. 
The program evaluates the sum of integers 0, ..., N-1, where N is argv[1] 
or the default value. To do so it creates N threads, each of which is 
responsible to increment the global variable sum by one of the summands.

*/

#include "ex1.h"

int main(int argc, char *argv[]){
    int N = (argc==2)? atoi(argv[1]) : DEFAULT_NUMBER_OF_THREADS;
    pthread_t * threads = (pthread_t *)malloc(N * sizeof(pthread_t));

    struct timeval Start, Stop, Diff;
    int i;

    gettimeofday(&Start, NULL);
    fprintf(stdout, "Thread 0. PID:%d, TID:%ld.\n", getpid(), pthread_self());
    fprintf(stdout,"Thread 0. Create threads.\n");

    for (i=0; i<N; i++)
        if (pthread_create(&threads[i], NULL, WorkFunction, (void*)i))
            fprintf(stderr,"Thread creation failed.\n");
    
    for (i=0; i<N; i++)
        if (pthread_join(threads[i], NULL))
            fprintf(stderr,"join thread failed.\n");


    fprintf(stdout,"Thread 0. Exits.\n");
    printf("Sum = %d\n", Sum);
    gettimeofday(&Stop, NULL);
    timersub(&Stop, &Start, &Diff);
    fprintf(stdout,"Time: %ld.%ld usec\n", Diff.tv_sec, Diff.tv_usec);
    free(threads);
    return 0;
}

void* WorkFunction(void* Arg){
    pthread_mutex_lock(&Mutex);
    Sum += (int) Arg;
    pthread_mutex_unlock(&Mutex); 
    return NULL;
}
