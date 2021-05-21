#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define N 4

sem_t sem1, sem2;
int foi = 0;

void * t1(void * arg) {
    sem_wait(&sem2);
    printf("Volte sempre! \n");
    pthread_exit(NULL);
}

void * t2(void * arg) {
    sem_wait(&sem1);
    printf("Fique a vontade \n");
     if (foi) {
        sem_post(&sem2);
    } else {
        foi++;
    }
    sem_post(&sem1);
    pthread_exit(NULL);
}

void * t3(void * arg) {
    sem_wait(&sem1);
    printf("Sente-se por favor. \n");
     if (foi) {
        sem_post(&sem2);
    } else {
        foi++;
    }
    sem_post(&sem1);
    pthread_exit(NULL);
}

void * t4(void * arg) {
    printf("Seja bem-vindo!. \n");
    sem_post(&sem1);
    pthread_exit(NULL);
}

int main() {
    pthread_t tid[N];
    sem_init(&sem1, 0, 0);
    sem_init(&sem2, 0, 0);

    if(pthread_create(&tid[0], NULL, t1, NULL)) {
        printf("Problema ao criar a thread t1.");
        exit(-1);
    }

    if(pthread_create(&tid[1], NULL, t2, NULL)) {
        printf("Problema ao criar a thread t2.");
        exit(-1);
    }

    if(pthread_create(&tid[2], NULL, t3, NULL)) {
        printf("Problema ao criar a thread t3.");
        exit(-1);
    }

    if(pthread_create(&tid[3], NULL, t4, NULL)) {
        printf("Problema ao criar a thread t4.");
        exit(-1);
    }

    int i;
    for (i = 0; i < 4; i++) {
        if(pthread_join(tid[i], NULL)) {
            printf("Problema de join. \n");
        exit(-1);
        }
    }

    sem_destroy(&sem1);

    pthread_exit(NULL);
}