#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include "timer.h"

int nThreads;
long long int N;

double calculatePi(long long int n) {
  double pi = 0, aux;
  int i, num = 1;

  for (i = 0; i < n; i += 2) {
    aux = 1.0 / (i + 1);
    pi += num * aux;
    num = num * (-1);
  }

  return 4 * pi;
}

void *calculatePiConc(void *arg) {
  int localTid = *(int *)arg;
  
  double aux; 
  double piPartial = 0;
  
  double *ret;
  ret = (double*) malloc(sizeof(double));
  
  int i;
  for (i = localTid*2; i < N; i += (2*nThreads)) {
    aux = 1.0 / (i + 1);
    piPartial += aux;

    if (nThreads == 1) {
      piPartial = piPartial * (-1);
    }    
  }

  if (localTid % 2) {
    piPartial = piPartial * (-1);
  }

  *ret = piPartial;
  pthread_exit((void *) ret);
}

int main(int argc, char *argv[]) {
  double *returnValue;
  double piSeq = 0, piConc = 0;
  double start, finish, timeSeq, timeConc;
  long int i;
  pthread_t *tid;
  int *localTid;

  if (argc < 3) {
    fprintf(stderr, "Types: %s <array dimension> <number of threads>\n", argv[0]);
    return 1;
  }

  N = atoll(argv[1]);
  nThreads = atoi(argv[2]);

  // Sequential
  GET_TIME(start);
  piSeq = calculatePi(N);
  GET_TIME(finish);
  timeSeq = finish - start;

  // Concurrent
  GET_TIME(start);
  tid = (pthread_t *) malloc(sizeof(pthread_t) * nThreads);
  if (tid == NULL) {
    fprintf(stderr, "ERRO--malloc\n");
    return 2;
  }

  localTid = malloc(sizeof(int) * nThreads);
  if (localTid == NULL) {
    printf("ERROR--malloc\n");
    return 2;
  }

  for (i = 0; i < nThreads; i++) {
    localTid[i] = i;

    if (pthread_create(tid+i, NULL, calculatePiConc, &localTid[i])) {
      fprintf(stderr, "ERRO--pthread_create\n");
      return 3;
    }
  }

  for (i = 0; i < nThreads; i++) {
    if (pthread_join(*(tid+i), (void *)&returnValue)) {
      fprintf(stderr, "ERRO--pthread_join\n");
      return 3;
    }
    piConc += *returnValue;
    free(returnValue);
  }

  piConc = 4 * piConc;
  GET_TIME(finish);
  timeConc = finish - start;

  printf("Tempo Sequencial: %lf\n", timeSeq);
  printf("Tempo Concorrente: %lf\n", timeConc);
  printf("Ganho de desempenho: %lf\n", timeSeq/timeConc);
  printf("Número sequencialmente: %.15lf \n", piSeq);
  printf("Número concorrentemente: %.15lf \n", piConc);
  printf("Número como base para a comparação: %.15lf \n", M_PI);
  printf("Erro Sequencial: %.15lf \n", (M_PI - piSeq));
  printf("Erro Concorrente: %.15lf \n", (M_PI - piConc));
}