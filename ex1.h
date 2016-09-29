#ifndef SHAREFILE_INCLUDED
#define SHAREFILE_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h> 
#include <pthread.h>
#include <math.h>

#define DEFAULT_NUMBER_OF_PROCESSES 12
#define TOTAL_ITERATIONS 10000000

#ifdef  MAIN_FILE
 int sum = 0;
 int NUMBER_OF_THREADS = 6;
 float* A;
 pthread_mutex_t Mutex = PTHREAD_MUTEX_INITIALIZER;
#else
 extern int sum;
 extern int NUMBER_OF_THREADS;
 extern float* A;
 extern pthread_mutex_t Mutex;
#endif

void* work_function(void *);
void * thread_function(void *);

#endif

