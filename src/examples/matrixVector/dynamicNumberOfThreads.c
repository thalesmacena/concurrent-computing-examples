#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include"../../util/timer.h"

float *mat; // Input matrix
float *vet; // Input vector
float *exitVector; // Exit Vector
int nThreads; // thread dimension

typedef struct {
  int id; // id of thread element
  int dim; // struct dimension input
} tArgs;

// Function performed by threads
void * task(void *arg) {
  tArgs *args = (tArgs*) arg;
  printf("Thread %d\n", args->id);
  int i,j;
  for (i = args->id; i<args->dim; i += nThreads) {
    for(j = 0; j < (args->dim); j++) {
      exitVector[i] += mat[i * (args->dim) + j] * vet[j];
    }
  }
  pthread_exit(NULL);
}

// Main function
int main(int argc, char* argv[]) {
  // Matrix dimension
  int dim;

  // pthread system id
  pthread_t *tid;

  // local thread id and dimension
  tArgs *args;

  // Time variables
  double start, finish, elapsed;

  // Reading and evaluation of input parameters
  if (argc<3) {
    printf("type: %s <Matrix Dimension> <number of threads> \n", argv[0]);

    return 1;
  }

  dim = atoi(argv[1]);
  nThreads = atoi(argv[2]);
  if (nThreads > dim) {
    nThreads = dim;
  }

  // Memory allocation for data structures
  mat = malloc(sizeof(float) * dim * dim);
  if (mat == NULL) {
    printf("ERROR--malloc\n");
    return 2;
  }

  vet = malloc(sizeof(float) * dim);
  if (vet == NULL) {
    printf("ERROR--malloc\n");
    return 2;
  }

  exitVector = malloc(sizeof(float) * dim);
  if (exitVector == NULL) {
    printf("ERROR--malloc\n");
    return 2;
  }

  // Initialization of data structures
  int i;
  int j;
  for(i = 0; i < dim; i++) {
    for(j = 0; j < dim; j++) {
      mat[i*dim+j] = 1;
    }

    vet[i] = 1;
    exitVector[i] = 0;
  }

  // Multiplication of the matrix by the vector
  GET_TIME(start);

  // Structures Allocation
  tid = (pthread_t*) malloc(sizeof(pthread_t)*nThreads);
  if (tid==NULL) {
    puts("ERROR--malloc");
    return 2;  
  }

  args = (tArgs*) malloc(sizeof(tArgs)*nThreads);
  if (args==NULL) {
    puts("ERROR--malloc");
    return 2;  
  }

  // Threads creation
  for(i = 0; i < nThreads; i++) {
    (args+i)->id = i;
    (args+i)->dim = dim;
    if (pthread_create(tid+i, NULL, task, (void*) (args+i))) {
      puts("ERROR--pthread_create");
      return 3;
    }
  }

  // Wait for threads to finish
  for(i = 0; i < nThreads; i++) {
    if (pthread_join(*(tid+i), NULL)) {
      puts("ERROR--pthread_join");
      return 3;
    }
  }

  // Results display
  // puts("Input matrix: ");
  // for(i = 0; i < dim; i++) {
  //   for(j = 0; j < dim; j++) {
  //     printf("%.lf ", mat[i*dim+j]);
  //   }
  //   puts("");
  // }

  // puts("Input vector:");
  // for(i = 0; i < dim; i++) {
  //   printf("%.lf ", vet[i]);
  // }
  // puts("");
  
  GET_TIME(finish);
  
  elapsed = finish - start;
  printf("multiplication of the matrix by the vector took %e seconds\n", elapsed);

  puts("Exit Vector:");
  for(i = 0; i < dim; i++) {
    printf("%.lf ", exitVector[i]);
  }
  puts("");

  // Free allocated memory
  free(mat);
  free(vet);
  free(exitVector);
  free(args);
  free(tid);

  return 0;
}