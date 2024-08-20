/*
Aluna: Eduarda Varela Fahr 
/* DRE : 120012515 
/* Laboratório: 1 
/* Codigo: Somar 1 ao array usando threads em C
*/
#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>
#include <math.h>


//Cria a estrutura de dados para armazenar os argumentos da thread
typedef struct {
   int idThread, mThreads,nThreads;
   int * arrayThreads;
   
} t_Args;

// Função responsável por somar 1 ao vetor e verificar por meio de impressão via tela que a soma foi realizada
void *somavetor (void *arg) {

  //typecarting do argumento
  t_Args args = *(t_Args*) arg;
  //divide em pedaços o vetor
   int pedaco = ceil(args.nThreads / (double)args.mThreads);
  // define o começo para cada thread do vetor
  int com = (args.idThread-1) * pedaco;
  //define o final para cada thread do vetor
  int fin = fmin((args.idThread) * pedaco, args.nThreads );
  //aloca um vetor novo resultado
  int *result = (int*)malloc(args.nThreads * sizeof(int));
  for (int j = com; j < fin; j++) {
        args.arrayThreads[j] = args.arrayThreads[j]+1;
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

// Função de verificação
void verifica(int *v1, int *v2, int N) {
    int iguais = 1; // Inicializa uma  flag como verdadeira se forem iguais

    for (int i = 0; i < N && iguais; i++) {
        if (v1[i] != v2[i]) {
            iguais = 0; // Caso os elementos sejam diferente a flag é falsa 
        }
    }
 //Printa a mensagem conforme o valor da flag
    if (iguais) {
        printf("Resultado de verificação correto\n");
    } else {
        printf("Resultado de verificação incorreto, os vetores são diferentes\n");
    }
}
int main(int argc, char* argv[]) {
    t_Args *args; //receberá os argumentos para a thread
    int M; //qtde de threads que serao criadas (recebida na linha de comando)
    int N;
    //verifica se o argumento 'qtde de threads' foi passado e armazena seu valor
    if(argc<3) {
       printf("--ERRO: informe a qtde de threads <%s> <M>\n", argv[0]);
       return 1;
    }
  // Recebendo M e N.
    M = atoi(argv[1]);
    N =atoi(argv[2]);
 //identificadores das threads no sistema
  pthread_t tid_sistema[M];
  //cria vetor
  int *array =Cria_array(N);
  //cria as threads
    for(int i=1; i<=M; i++) {
       printf("--Aloca e preenche argumentos para thread %d\n", i);
       args = malloc(sizeof(t_Args));
       if (args == NULL) {
          printf("--ERRO: malloc()\n"); 
       return 2;
    }
    // define os args para as threads
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

   // verifica se os array são iguais   
  verifica(args->arrayThreads,array,N);
  free(array);

}
