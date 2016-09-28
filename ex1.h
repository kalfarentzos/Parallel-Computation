#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h> 
#include <pthread.h>
#include <math.h>

#define DEFAULT_NUMBER_OF_THREADS 50
#define DEFAULT_NUMBER_OF_PROCESSES 50

#ifndef SHAREFILE_INCLUDED
#define SHAREFILE_INCLUDED
    #ifdef  MAIN_FILE
    int sum = 0;
    pthread_mutex_t Mutex = PTHREAD_MUTEX_INITIALIZER;
    #else
    extern int sum;
    pthread_mutex_t Mutex;
    #endif
#endif

void* WorkFunction(void* Arg);
