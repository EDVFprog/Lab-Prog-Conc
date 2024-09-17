#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS 2

long int soma = 0; // Variável compartilhada entre as threads
pthread_mutex_t mutex; // Variável de bloqueio para exclusão mútua
pthread_cond_t cond1,cond2; // variaveis de condições 
int cont = 0; // Contador de múltiplos
int flag=0;// flag que sinaliza quando achado um multiplo


void *ExecutaTarefa(void *arg) {
    

    for (int i = 0; i < 100000; i++) {
        // exclusividade para cada thread
        pthread_mutex_lock(&mutex);
        soma++;// incrementa a variavel soma
        //checa se a soma é multiplo de  10
        if (soma % 10 == 0) {
            flag=1;
            pthread_cond_signal(&cond1);// envia o sinal para a thread para printar o valor do múltiplo
            pthread_cond_wait(&cond2, &mutex);// bloqueia a thread até que seja printado o valor
            
        }
        pthread_mutex_unlock(&mutex);
        //termina se o valor de soma for maior do que os 20 primeiros multiplos
        if(cont>=20){
           break;
           }
          
    }

    printf("Thread Executa Tarefa - terminou!\n");
    pthread_exit(NULL);
}

void *extra(void *args) {
// exclusividade para cada thread
    pthread_mutex_lock(&mutex);
    // imprime o múltipĺo se achado
    while (cont < 20) {
      if(flag){
         printf("soma = %ld\n", soma);
         cont++;// incrementa o contador
         flag=0;// reseta a flag para o próximo múltiplo
         pthread_cond_signal(&cond2);// libera a thread após printar
        }
     
      else{
   
        pthread_cond_wait(&cond1, &mutex);// bloqueia a thread caso nenhum multiplo seja encontrado
        }
        
    }

    pthread_mutex_unlock(&mutex);
    printf("Extra: terminou!\n");
   
    pthread_exit(NULL);
}

// Fluxo principal
int main() {
    pthread_t threads[NTHREADS];

    /* Inicializa o mutex (bloqueio de exclusão mútua) e as variaveis de condição */
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond1, NULL);
    pthread_cond_init(&cond2, NULL);

    /* Cria as threads */
    pthread_create(&threads[0], NULL, ExecutaTarefa, NULL);
    pthread_create(&threads[1], NULL, extra, NULL);

    /* Espera todas as threads completarem */
    for (int i = 0; i < NTHREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Valor  'soma' = %ld\n", soma);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond1);
    pthread_cond_destroy(&cond2);

    return 0;
}
