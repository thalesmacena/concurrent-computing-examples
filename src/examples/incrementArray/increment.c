#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>

// Define the number of threads
#define NTHREADS 2

// Define the array length
#define ALENGTH 10000

// Creaate global array and get the size
int array[ALENGTH];

// function performed by each thread
void *IncrementArray (void *arg) {
  int posThread = * (int*) arg;
 
  int i;
  
  for (i = posThread; i < ALENGTH; i += NTHREADS) {
    array[i]++;
  }

  pthread_exit(NULL);
}

// main function
int main() {
  // thread id
  pthread_t tid_sistema[NTHREADS];

  // thread index
  int thread;

  // local thread id
  int tid_local[NTHREADS];

  // Create all threads
  for(thread=0; thread<NTHREADS; thread++) {
    // Defines the starting position that each thread will start
    tid_local[thread] = thread;

    // Create a new thread
    if (pthread_create(&tid_sistema[thread], NULL, IncrementArray, (void*) &tid_local[thread])) {
      printf("--ERRO: pthread_create()\n"); exit(-1);
    }
  }

  // Await all threads stop
   for (thread=0; thread<NTHREADS; thread++) {
    if (pthread_join(tid_sistema[thread], NULL)) {
         printf("--ERRO: pthread_join() \n"); exit(-1); 
    } 
  }

  // Checks if the array has been correctly incremented
  for (thread=0; thread < ALENGTH; thread++) {
    if (array[thread] != 1) {
         printf("--ERRO: Array has not been incremented correctly \n"); exit(-1); 
    } 
  }

  printf("Array incremented correctly \n");

  // disconnect the end of the mother from the end of the program
  pthread_exit(NULL);
}