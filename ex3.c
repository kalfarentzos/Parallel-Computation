/* ex3.c
|----------------------------------------------------------|
| Authors:  Kalfarentzos Konstantinos Georgios A.M.: 2444  |
|           Karanikolas Nikolaos               A.M.: 2449  |
|----------------------------------------------------------|

This is a simple demonstration for didactic purposes of the use of 
POSIX threads to parallelize a computation in the absence of dependencies. 
The program evaluates A[i] = sqrt(i*1.1) + sqrt(i*0.9) * sqrt(i) where i is in 
{0, 1, TOTAL_ITERATIONS}. To do so it creates NUMBER_OF_THREADS threads, each 
of which is responsible to calculate TOTAL_ITERATIONS/NUMBER_OF_THREADS 
entries of A.
*/

#define MAIN_FILE
#include "ex1.h"

int main(int argc, char *argv[]){
    NUMBER_OF_THREADS = (argc==2)? argv[1]: NUMBER_OF_THREADS;
    int N = NUMBER_OF_THREADS;
    A = (float *) malloc(TOTAL_ITERATIONS * sizeof(float));
    
    struct timeval start, stop, diff;
    
    pthread_t* threads = (pthread_t *) malloc(N * sizeof(pthread_t));     

    gettimeofday(&start, NULL);
    fprintf(stdout, "Thread 0. PID:%d, TID:%ld.\n", getpid(), pthread_self());
    fprintf(stdout, "Thread 0. Creates %d threads.\n", N);

    for(int i = 0; i < N; i++)
       if (pthread_create(&threads[i], NULL, thread_function, (void *)i))
           fprintf(stderr,"Thread creation failed.\n");
        
    for (int i = 0; i < N; i++)
        if (pthread_join(threads[i], NULL))
            fprintf(stderr,"Join thread failed.\n");

    gettimeofday(&stop, NULL);
    timersub(&stop, &start, &diff);
    fprintf(stdout, "Time: %ld.%ld usec\n", diff.tv_sec, diff.tv_usec);
    fprintf(stdout,"Thread 0. Exits.\n");
    return 0;
}

void * thread_function(void* Arg){
    int k = (int)Arg;
    int start = (int)(k * float(TOTAL_ITERATIONS) / NUMBER_OF_THREADS);
    int end = (int)((k+1) * float(TOTAL_ITERATIONS) / NUMBER_OF_THREADS);
                
    for (int i = start; i < end; i++)
        A[i] = sqrt(i*1.1) + sqrt(i*0.9) * sqrt(i);

    return NULL;
}

