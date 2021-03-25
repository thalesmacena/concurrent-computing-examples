#include<stdio.h>
#include<pthread.h>

// define the number of threads
#define NTHREADS 100

int vetor[NTHREADS];

// function that the thread will perform
void * task (void * arg) {
  int ident = * (int *) arg;

  vetor[ident] = ident + 1;
 
  printf("I'm the thread %d!\n", ident + 1);

  pthread_exit(NULL);
}

// main function
int main(void) {
  // thread id
  pthread_t tid[NTHREADS];

  // local thread id
  int ident[NTHREADS];

  int i;

  // create all threads
  for(i = 0; i < NTHREADS; i++) {
    ident[i] = i;
    // create a new thread
    if (pthread_create(&tid[i], NULL, task, (void *)&ident[i]))
      printf("ERRO --pthread_create\n");
      exit(-1);
  }

  // waits for all threads to finish
  for(i = 0; i < NTHREADS; i++) {
    if (pthread_join(tid[i], NULL))
      printf("ERRO --pthread_join\n");
  }

  // send hello world message
  printf("I'm the main thread!\n");

  for(i = 0; i < NTHREADS; i++) {
    printf("%d ", vetor[i]);
  }

  // disconnect the end of the mother from the end of the program
  pthread_exit(NULL);
  return 0;
}