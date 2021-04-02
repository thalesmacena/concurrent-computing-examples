#include<stdio.h>
#include<stdlib.h>

float *mat; // Input matrix
float *vet; // Input vector
float *exitVector; // Exit Vector

int main(int argc, char* argv[]) {
  // Matrix dimension
  int dim;

  // Reading and evaluation of input parameters
  if (argc<2) {
    printf("type: %s <Matrix Dimension>\n", argv[0]);

    return 1;
  }

  dim = atoi(argv[1]);

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
  for(i = 0; i < dim; i++) {
    for(j = 0; j < dim; j++) {
      exitVector[i] += mat[i*dim+j]*vet[j];
    }
  }

  // Results display
  puts("Input matrix: ");
  for(i = 0; i < dim; i++) {
    for(j = 0; j < dim; j++) {
      printf("%.lf ", mat[i*dim+j]);
    }
    puts("");
  }

  puts("Input vector:");
  for(i = 0; i < dim; i++) {
    printf("%.lf ", vet[i]);
  }
  puts("");
  

  puts("Exit Vector:");
  for(i = 0; i < dim; i++) {
    printf("%.lf ", exitVector[i]);
  }
  puts("");

  // Free allocated memory
  free(mat);
  free(vet);
  free(exitVector);

  return 0;
}