#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>
#include <math.h>


//cria a estrutura de dados para armazenar os argumentos da thread
typedef struct {
   int idThread, mThreads,nThreads;
   int * arrayThreads;
   
} t_Args;

void *somavetor (void *arg) {

  //typecarting do argumento
  t_Args args = *(t_Args*) arg;
  
   int chunk_size = ceil(args.nThreads / (double)args.mThreads);

// e consertar o join
  int start = (args.idThread-1) * chunk_size;
  int end = fmin((args.idThread) * chunk_size, args.nThreads );

        for (int j = start; j < end; j++) {
            args.arrayThreads[j] = args.arrayThreads[j]+1;
            printf("%d",args.arrayThreads[j]) ;
        }


  free(arg); //libera a memoria que foi alocada na main

  pthread_exit(NULL);
}

// Cria um array de tamanho N e retorna um ponteiro para ele
int* Cria_array(int N) {
    int* vetor = (int*)malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        vetor[i] = i + 1;
    }

    return vetor;
}

//Função para teste do vetor
//Complementar a Main para pegar os argumentos para a thread e os testes
int main(int argc, char* argv[]) {
    t_Args *args; //receberá os argumentos para a thread
    int M; //qtde de threads que serao criadas (recebida na linha de comando)
    int N;
    //verifica se o argumento 'qtde de threads' foi passado e armazena seu valor
    if(argc<2) {
       printf("--ERRO: informe a qtde de threads <%s> <M>\n", argv[0]);
       return 1;
    }
    M = atoi(argv[1]);
    N =atoi(argv[2]);
 //identificadores das threads no sistema
  pthread_t tid_sistema[M];

  //cria as threads
  for(int i=1; i<=M; i++) {
    printf("--Aloca e preenche argumentos para thread %d\n", i);
    args = malloc(sizeof(t_Args));
    if (args == NULL) {
      printf("--ERRO: malloc()\n"); 
      return 2;
    }
    int *array =Cria_array(N);
    args->idThread = i; 
    args->mThreads = M; 
    args->arrayThreads =  array;
    args->nThreads =N;
       
    printf("--Cria a thread %d\n", i);
    if (pthread_create(&tid_sistema[i-1], NULL, somavetor, (void*) args)) {
      printf("--ERRO: pthread_create()\n"); 
    }
  }
   // Esperar todas as threads terminarem
    for (int i = 0; i < M; i++) {
        if (pthread_join(tid_sistema[i], NULL)) {
             printf("--ERRO: pthread_join() da thread %d\n", i);
        }
        }
  //log da função principal
  printf("--Thread principal terminou\n");

}
