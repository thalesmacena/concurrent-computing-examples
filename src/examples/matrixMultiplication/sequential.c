#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include"timer.h"

float *mat1; // first input matrix
float *mat2; // second input matrix
float *exitMatrix; // Exit Matrix

// Main function
int main(int argc, char* argv[]) {
  // Matrix dimension
  int dim;

  // Time variables
  double start, finish, total;

  // Reading and evaluation of input parameters
  GET_TIME(start);
  if (argc<2) {
    printf("type: %s <Matrix Dimension> \n", argv[0]);

    return 1;
  }

  dim = atoi(argv[1]);

  // Memory allocation for data structures
  mat1 = malloc(sizeof(float) * dim * dim);
  if (mat1 == NULL) {
    printf("ERROR--malloc \n");
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
  int i,j,k;

  for(i = 0; i < dim; i++) {
    for(j = 0; j < dim; j++) {
      mat1[i*dim+j] = 1;
      mat2[i*dim+j] = 1;
      exitMatrix[i*dim+j] = 0;
    }
  }

  // Multiplication of the matrix by matrix
  for (i = 0; i < dim; i++) {
    for (j = 0; j < dim; j++) {
      for (k = 0; k < dim; k++) {
        exitMatrix[j * dim + i] += mat1[j*dim+k] * mat2[k*dim+i];
      }
    }
  }
  
  // Validation
  // for(i = 0; i < dim; i++) {
  //    for(j = 0; j < dim; j++) {
  //     if (exitMatrix[i*dim+j] != dim) {
  //       puts("ERROR--Validation");
  //       return 4;
  //     };
  //   }
  // }

  // Free allocated memory  
  free(mat1);
  free(mat2);
  free(exitMatrix);

  // benchmark
  GET_TIME(finish);
  total = finish - start;
  printf("Totaltime took %e seconds\n", total);

  return 0;
}