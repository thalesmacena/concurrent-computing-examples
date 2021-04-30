#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

long int N;
long int NTHREADS;
long int* ARRAY;
long int* TESTE;

pthread_mutex_t LOCK;
pthread_cond_t COND;
long int CONT;

// função barreira
void barreira() {
    pthread_mutex_lock(&LOCK);
    CONT++;
    if (CONT < NTHREADS) {
        pthread_cond_wait(&COND, &LOCK);
    } else {
        CONT = 0;
        pthread_cond_broadcast(&COND);
    }
    pthread_mutex_unlock(&LOCK);
}

// função executada pelas threads
void *tarefa(void *arg) {
  long int localId = (long int) arg;
  long int aux;

  for (long int i = 1; i < N; i = i*2) {
    long int indice = localId - i;
    if (!(indice < 0)) {
      aux = ARRAY[indice];
    }

    barreira();

     if (!(indice < 0)) {
      ARRAY[localId] = ARRAY[localId] + aux;
    }

    barreira();
  }


  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  pthread_t *tid;

  double aux;

  pthread_mutex_init(&LOCK, NULL);
  pthread_cond_init(&COND, NULL);
  
  if (argc < 2) {
    fprintf(stderr, "Type: %s <array dimension>\n", argv[0]);
    return 1;
  }

  N = atoll(argv[1]);
  NTHREADS = N;

  // Checa se a dimensão do array é potencia de 2
  aux = log(N) / log(2);

  if (aux - trunc(aux) != 0) {
    fprintf(stderr, "O numero: %s nao e raiz de 2\n", argv[1]);
    return 1;
  }

  // ALOCAÇÃO DE ESPAÇO
  // Array de Threads
  tid = (pthread_t *)malloc(sizeof(pthread_t) * NTHREADS);
	if (tid == NULL) {
		fprintf(stderr, "ERRO--malloc\n");
		return 2;
	}

  // Concorrente
  ARRAY = malloc(N * sizeof(long int *));
	if (ARRAY == NULL) {
		printf("ERROR--malloc\n");
		return 2;
	}

  // Sequencial para validação
  TESTE = malloc(N * sizeof(long int *));
	if (TESTE == NULL) {
		printf("ERROR--malloc\n");
		return 2;
	}

  // GERAÇÃO DO ARRAY
  for (long int i = 0; i < N; i++) {
		// scanf("%f | ", &ARRAY[i]);
		aux = rand() % 10; // numeros aleatorios entre 0 e 9
		ARRAY[i] = (long int) aux;
	}
	// printf("\n");

  // print do array gerado
  // printf("Resultado Concorrente:\n");
  // for (long int i = 0; i < N; i++) {
  //   printf("%ld | ", ARRAY[i]);
  // }
  // printf("\n");

  // EXECUÇÃO
  // SEQUENCIAL
  TESTE[0] = ARRAY[0];
  for (long int i = 1 ; i < N; i++) {
    TESTE[i] = ARRAY[i] + TESTE[i-1];
  }

  // CONCORRENTE
  for (long int i = 0; i < NTHREADS; i++) {
		if (pthread_create(tid + i, NULL, tarefa, (void *) i)) {
			fprintf(stderr, "ERRO--pthread_create\n");
			return 3;
		}
	}

	for (long int i = 0; i < NTHREADS; i++) {
		if (pthread_join(*(tid + i), NULL)) {
			fprintf(stderr, "ERRO--pthread_join\n");
			return 3;
		}
	}

  // PRINT DOS RESULTADOS
  // Concorrente
  // printf("Resultado Concorrente:\n");
  // for (long int i = 0; i < N; i++) {
  //   printf("%ld | ", ARRAY[i]);
  // }
  // printf("\n");

  // Sequencial
  // printf("Resultado Sequencial:\n");
  // for (long int i = 0; i < N; i++) {
  //   printf("%ld | ", TESTE[i]);
  // }
  // printf("\n");

  // VALIDAÇÃO
  for (long int i = 0; i < N; i++) {
    if (TESTE[i] != ARRAY[i]) {
      fprintf(stderr, "\nERRO--Validação: TESTE[%ld]=%ld | ARRAY[%ld]=%ld\n\n", i, TESTE[i], i, ARRAY[i]);
			return 4;
    }
  }

  printf("\nA execução passou na validação\n\n");

  free(ARRAY);
  free(TESTE);
  pthread_mutex_destroy(&LOCK);
  pthread_cond_destroy(&COND);

  return 0;
}
