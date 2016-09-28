#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h> 
#include <pthread.h>

#define DEFAULT_NUMBER_OF_THREADS 50

void* WorkFunction(void* Arg);
int Sum = 0;
pthread_mutex_t Mutex = PTHREAD_MUTEX_INITIALIZER;
