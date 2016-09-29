/* ex2.c
|----------------------------------------------------------|
| Authors:  Kalfarentzos Konstantinos Georgios A.M.: 2444  |
|           Karanikolas Nikolaos               A.M.: 2449  |
|----------------------------------------------------------|

This is a simple demonstration for didactic purposes of an (erroneous) use of 
a (naively thought) shared global variable by processes.
*/

#define MAIN_FILE
#include "ex1.h"

int main(int argc, char *argv[]){
    int i;
    int pid;
    int status;
    int N = (argc==2)? atoi(argv[1]) : DEFAULT_NUMBER_OF_PROCESSES;
    
    struct timeval start, stop, diff;
    pid_t* processes = (pid_t *) malloc(N * sizeof(pid_t));
    gettimeofday(&start, NULL);
    fprintf(stdout,"Main Process. PID:%d.\n", getpid());
    fprintf(stdout,"Main Process. Creates %d children.\n", N);
    for(i = 0; i < N; i++){
        if ((pid = fork()) < 0)
            fprintf(stderr,"ERROR: fork process %d failed.\n", i);
        
        if (!pid){
            // Child calls work function and exits.
            work_function((void *)(i+1));
            exit(0);
        }
        processes[i] = pid;
    }
    fprintf(stdout,"Main Process. Wait the  children.\n");

    for (i = 0; i < N; i++)
        waitpid(processes[i], &status, 0);
    free(processes);
    
    printf("Pseudo sum = %d\n", sum);
    gettimeofday(&stop, NULL); 
    timersub(&stop, &start, &diff);
        
    fprintf(stdout,"Time: %ld.%ld usec\n", diff.tv_sec, diff.tv_usec);
    fprintf(stdout, "Main Process. Exits.\n");
    return 0;
}
            
void * work_function(void * Arg){
    int i = (int)Arg;   
    fprintf(stdout,"Child Process %d. PID:%d.\n", i, getpid());
    fprintf(stdout,"Child Process %d. Sleeps.\n", i); 
    sum += i;
    fprintf(stdout,"Child Process %d. Exits.\n", i);
    return NULL;
}
