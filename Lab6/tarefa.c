//Programa concorrente que cria e faz operacoes sobre uma lista de inteiros utilizando o padrão leitor e escritor

#include <stdio.h>
#include <stdlib.h>
#include "list_int.h"
#include <pthread.h>
#include "timer.h"
#include "leitor_escritor.h" // importando a biblioteca criada

#define QTDE_OPS 100 //quantidade de operacoes sobre a lista (insercao, remocao, consulta)
#define QTDE_INI 100 //quantidade de insercoes iniciais na lista
#define MAX_VALUE 100 //valor maximo a ser inserido

// estrutura para a lista encadeada
struct list_node_s* head_p = NULL; 

//qtde de threads no programa
int nthreads;

//tarefa das threads
void* tarefa(void* arg) {
   long int id = (long int) arg;
   int op;
   int in, out, read; 
   in=out=read = 0; 

   //realiza operacoes de consulta (98%), insercao (1%) e remocao (1%)
   for(long int i=id; i<QTDE_OPS; i+=nthreads) {
      op = rand() % 100;
      if(op<98) {
	  EntraLeitura(); /* chama a leitura*/    
         Member(i%MAX_VALUE, head_p);   /* Ignore return value */
	 SaiLeitura();    /* sai da  leitura*/   
	 read++;
      } else if(98<=op && op<99) {
	 EntraEscrita(); /* chama a escrita */    
         Insert(i%MAX_VALUE, &head_p);  /* Ignore return value */
	 SaiEscrita();     /* sai da  escrita*/ 
	 in++;
      } else if(op>=99) {
	  EntraEscrita() ; /* chama a escrita */     
         Delete(i%MAX_VALUE, &head_p);  /* Ignore return value */
	 SaiEscrita();    /* sai da  escrita*/ 
	 out++;
      }
   }
   //registra a qtde de operacoes realizadas por tipo
   printf("Thread %ld: in=%d out=%d read=%d\n", id, in, out, read);
   pthread_exit(NULL);
}

/*-----------------------------------------------------------------*/
int main(int argc, char* argv[]) {
   pthread_t *tid;
   double ini, fim, delta;
   
   //verifica se o numero de threads foi passado na linha de comando
   if(argc<2) {
      printf("Digite: %s <numero de threads>\n", argv[0]); return 1;
   }
   nthreads = atoi(argv[1]);

   //insere os primeiros elementos na lista
   for(int i=0; i<QTDE_INI; i++)
      Insert(i%MAX_VALUE, &head_p);  /* Ignore return value */
   

   //aloca espaco de memoria para o vetor de identificadores de threads no sistema
   tid = malloc(sizeof(pthread_t)*nthreads);
   if(tid==NULL) {  
      printf("--ERRO: malloc()\n"); return 2;
   }

   //tomada de tempo inicial
   GET_TIME(ini);
   //inicializa a variavel mutex
   pthread_mutex_init(&mutex, NULL);
   pthread_cond_init(&cond_leit, NULL);
   pthread_cond_init(&cond_escr, NULL);
   
   //cria as threads
   for(long int i=0; i<nthreads; i++) {
      if(pthread_create(tid+i, NULL, tarefa, (void*) i)) {
         printf("--ERRO: pthread_create()\n"); return 3;
      }
   }
   
   //aguarda as threads terminarem
   for(int i=0; i<nthreads; i++) {
      if(pthread_join(*(tid+i), NULL)) {
         printf("--ERRO: pthread_join()\n"); return 4;
      }
   }

   //tomada de tempo final
   GET_TIME(fim);
   delta = fim-ini;
   printf("Tempo: %lf\n", delta);

   //libera o mutex
   pthread_mutex_destroy(&mutex);
   //libera o espaco de memoria do vetor de threads
   free(tid);
   //libera o espaco de memoria da lista
   Free_list(&head_p);

   return 0;
}  /* main */
