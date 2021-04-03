#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include"timer.h"

float *mat1; // first input matrix
float *mat2; // second input matrix
float *exitMatrix; // Exit Matrix
int nThreads; // thread dimension

typedef struct {
  int id; // id of thread element
  int dim; // struct dimension input
} tArgs;

// Function performed by threads to square matrix multiplication
void * task(void *arg) {
  tArgs *args = (tArgs*) arg;
  printf("Thread %d\n", args->id);

  int i,j,k;
  float temp;

  for (i = args->id; i < (args->dim); i += nThreads) {
    for (j = 0; j < (args->dim); j++) {
      temp = 0;
      for(k = 0; k < (args->dim); k++) {
        temp += mat1[j*(args->dim)+k] * mat2[k*(args->dim)+i];
      }
      exitMatrix[j * (args->dim) + i] = temp;
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
  double start, finish, total, dataInit, threadExecute, dataFree;

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
  mat1 = malloc(sizeof(float) * dim * dim);
  if (mat1 == NULL) {
    printf("ERROR--malloc\n");
    return 2;
  }

  mat2 = malloc(sizeof(float) * dim * dim);
  if (mat2 == NULL) {
    printf("ERROR--malloc\n");
    return 2;
  }

  exitMatrix = malloc(sizeof(float) * dim * dim);
  if (exitMatrix == NULL) {
    printf("ERROR--malloc\n");
    return 2;
  }

  // Initialization of data structures
  GET_TIME(start);
  int i;
  int j;
  for(i = 0; i < dim; i++) {
    for(j = 0; j < dim; j++) {
      mat1[i*dim+j] = 1;
      mat2[i*dim+j] = 1;
      exitMatrix[i*dim+j] = 0;
    }
  }
  GET_TIME(finish);
  dataInit = finish - start;

  // Multiplication of the matrix by matrix
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
  
  GET_TIME(finish);
  threadExecute = finish - start;
  

  // Validation
  for(i = 0; i < dim; i++) {
     for(j = 0; j < dim; j++) {
      if (exitMatrix[i*dim+j] != dim) {
        puts("ERROR--Validation");
        return 4;
      };
    }
  }

  // Free allocated memory
  GET_TIME(start);
  
  free(mat1);
  free(mat2);
  free(exitMatrix);
  free(args);
  free(tid);

  GET_TIME(finish);
  dataFree = finish - start;

  // benchmark
  total = dataInit + threadExecute + dataFree;
  printf("Data structure init took %e seconds\n", dataInit);
  printf("Matrix Creation and execution took %e seconds\n", threadExecute);
  printf("Data Free took %e seconds\n", dataFree);
  printf("Totaltime took %e seconds\n", total);

  return 0;
}