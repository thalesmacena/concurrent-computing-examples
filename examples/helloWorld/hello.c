#include<stdio.h>
#include<pthread.h>

// function that the thread will perform
void * task (void * arg) {
  printf("I'm the new thread!\n");

  pthread_exit(NULL);
}

// main function
int main(void) {
  // thread id
  pthread_t tid;

  // create a new thread
  if (pthread_create(&tid, NULL, task, NULL))
    printf("ERRO --pthread_create\n");

  // send hello world message
  printf("I'm the main thread!\n");

  // disconnect the end of the mother from the end of the program
  pthread_exit(NULL);
  return 0;
}