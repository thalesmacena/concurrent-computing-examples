#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include "../../util/timer.h"

long int dim;
int nThreads;
double *vetor;

// Threads function
void * tarefa(void * arg) {
  long int id = (long int) arg;

  // thread block length
  long int blockLength = dim/nThreads;

  long int ini = id * blockLength;

  double *sumLocal;
  sumLocal = (double*) malloc(sizeof(double));
  if(sumLocal == NULL) {
    fprintf(stderr, "Erro-malloc\n");
    exit(1);
  }
  *sumLocal = 0;

  long int end;

  if(id ==nThreads - 1) {
    // Elemento Final (não processaddo) do bloco da thread
    end = dim;
  } else {
    // Trata o resto se houver
    end = ini + blockLength;
  }

  long int i;
  for (i = ini; i < end; i++) {
    *sumLocal += vetor[i];
  }

  pthread_exit((void *) sumLocal);
}

// Main
int main (int argc, char *argv[]) {
  long int i;
  double sumSeq, sumConc;
  double *returnValue;
  double start, finish, timeSeq, timeCunc;
  pthread_t *tid;

  if (argc < 3) {
    fprintf(stderr, "Types: %s <array dimension> <number of threads>\n", argv[0]);
    return 1;
  }

  dim = atoi(argv[1]);
  nThreads = atoi(argv[2]);

  vetor = (double*) malloc(sizeof(double)*dim);
  if (vetor == NULL) {
    fprintf(stderr, "ERRO--malloc\n");
    return 2;
  }

  // fill array
  for (i = 0; i < dim; i++) {
    vetor[i] = 1000.1/(i+1);
  }

  // Sequential
  sumSeq = 0;

  GET_TIME(start);
  
  for (i = 0; i < dim; i++) {
    sumSeq += vetor[i];
  }
  
  GET_TIME(finish);
  timeSeq = finish - start;

  // Concurrent
  GET_TIME(start);
  sumConc = 0;
  tid = (pthread_t *) malloc(sizeof(pthread_t) * nThreads);
  if (tid == NULL) {
    fprintf(stderr, "ERRO--malloc\n");
    return 2;
  }

  for(i = 0; i < nThreads; i++) {
    if (pthread_create(tid+i, NULL, tarefa, (void*) i)) {
      fprintf(stderr, "ERRO--pthread_create\n");
      return 3;
    };
  }

  // Wait threads finish
  for(i = 0; i < nThreads; i++) {
    if (pthread_join(*(tid+i), (void**) &returnValue)) {
      fprintf(stderr, "ERRO--pthread_join\n");
      return 3;
    };
    sumConc += *returnValue;
    free(returnValue);
  }
  GET_TIME(finish);
  timeCunc = finish - start;
  
  // print results
  printf("Sum seq: %lf\n", sumSeq);
  printf("Sum conc: %lf\n", sumConc);

  printf("time sequential: %lf\n", timeSeq);
  printf("time concurrent: %lf\n", timeCunc);

  //exit
  free(vetor);
  free(tid);

  return 0;
}