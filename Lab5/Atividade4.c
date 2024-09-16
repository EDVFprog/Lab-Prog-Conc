#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS 2

long int soma = 0; // Variável compartilhada entre as threads
pthread_mutex_t mutex; // Variável de bloqueio para exclusão mútua
pthread_cond_t cond;
int count = 0; // Contador de múltiplos

// Função executada pelas threads
void *ExecutaTarefa(void *arg) {
    long int id = (long int)arg;
    printf("Thread : %ld está executando...\n", id);

    for (int i = 0; i < 100000; i++) {
        pthread_mutex_lock(&mutex); // Bloqueia a seção crítica
        soma++;

        if (!(soma % 10)) {
            // Bloqueia a thread até receber o sinal da variável de condição
            pthread_cond_wait(&cond, &mutex);
        }

        pthread_mutex_unlock(&mutex); // Libera a seção crítica

        if (count >= 20) {
            break; // Interrompe o loop principal
        }
    }

    printf("Thread : %ld terminou!\n", id);
    pthread_exit(NULL);
}

// Função executada pela thread de log
void *extra(void *args) {
    printf("Extra : está executando...\n");

    while (count < 20) {
        printf("soma = %ld \n", soma);
        count++;

        // Sinaliza a variável de condição para liberar as threads bloqueadas
        pthread_cond_signal(&cond);
    }

    printf("Extra : terminou!\n");
    pthread_exit(NULL);
}

// Fluxo principal
int main() {
    pthread_t threads[NTHREADS];

    /* Inicializa o mutex (bloqueio de exclusão mútua) e a variável de condição */
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    /* Cria as threads */
    pthread_create(&threads[0], NULL, ExecutaTarefa, NULL);
    pthread_create(&threads[1], NULL, extra, NULL);

    /* Espera todas as threads completarem */
    for (int i = 0; i < NTHREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Value of 'soma' = %ld\n", soma);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}
