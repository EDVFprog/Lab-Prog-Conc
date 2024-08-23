#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h> 
#include <math.h>
//variaveis globais
//tamanho do vetor
long int n;
//vetor de elementos
float *vet;
//vetor de elementos
float *vetb;
// double 
//numero de threads
int nthreads;

//funcao executada pelas threads
//estrategia de divisao de tarefas: blocos de n/nthreads elementos
void *Prod (void *tid) {
  long int id = (long int) tid; //identificador da thread
  int ini, fim, bloco; //auxiliares para divisao do vetor em blocos
  float soma_local, *ret; //somatorio local
  
  bloco = n/nthreads; //tamanho do bloco de dados de cada thread
  ini = id*bloco; //posicao inicial do vetor
  fim = ini + bloco; //posicao final do vetor
  if (id==(nthreads-1)) fim = n; //a ultima thread trata os elementos restantes no caso de divisao nao exata

  //produto vetorial
  for(int i=ini; i<fim; i++) {
     soma_local += vet[i]*vetb[i];
  }

  //retorna o resultado do produto
  ret = malloc(sizeof(float));
  if (ret!=NULL) *ret = soma_local;
  else printf("--ERRO: malloc() thread\n");
  pthread_exit((void*) ret);
}
// Calcula a variação entre os programas concorrente e sequencial
double varRel(double vs,double vc){
  double e =sqrt(pow(((vs-vc)/vs),2));
  return e;
}

//funcao principal do programa
int main(int argc, char *argv[]) {
  FILE *arq; //arquivo de entrada
  size_t ret; //retorno da funcao de leitura no arquivo de entrada
	      
  double prod_ori; //soma registrada no arquivo
  float  soma_par_global; //resultados da soma
  float *soma_retorno_threads; //auxiliar para retorno das threads

  pthread_t *tid_sistema; //vetor de identificadores das threads no sistema

  //valida e recebe os valores de entrada
  if(argc < 3) { printf("Use: %s <arquivo de entrada> <numero de threads> \n", argv[0]); exit(-1); }

  //abre o arquivo de entrada com os valores para serem somados
  arq = fopen(argv[1], "rb");
  if(arq==NULL) { printf("--ERRO: fopen()\n"); exit(-1); }

  //le o tamanho do vetor (primeira linha do arquivo)
  ret = fread(&n, sizeof(long int), 1, arq);
  if(!ret) {
     fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo \n");
     return 3;
  }

  //aloca espaco de memoria e carrega o vetor de entrada
  vet = malloc (sizeof(float) * n);
  if(vet==NULL) { printf("--ERRO: malloc()\n"); exit(-1); }
  ret = fread(vet, sizeof(float), n, arq);
  
  //aloca espaco de memoria e carrega o vetorb de entrada
  vetb = malloc (sizeof(float) * n);
  if(vetb==NULL) { printf("--ERRO: malloc()\n"); exit(-1); }
   ret = fread(vetb, sizeof(float), n, arq);
  if(ret < n) {
     fprintf(stderr, "Erro de leitura dos elementos do vetor\n");
     return 4;
  }

  //le o numero de threads da entrada do usuario 
  nthreads = atoi(argv[2]);
  //limita o numero de threads ao tamanho do vetor
  if(nthreads>n) nthreads = n;

  //aloca espaco para o vetor de identificadores das threads no sistema
  tid_sistema = (pthread_t *) malloc(sizeof(pthread_t) * nthreads);
  if(tid_sistema==NULL) { printf("--ERRO: malloc()\n"); exit(-1); }

  //cria as threads
  for(long int i=0; i<nthreads; i++) {
    if (pthread_create(&tid_sistema[i], NULL, Prod, (void*) i)) {
       printf("--ERRO: pthread_create()\n"); exit(-1);
    }
  }


 
  //espera todas as threads terminarem e calcula a soma total das threads
  soma_par_global=0;
  for(int i=0; i<nthreads; i++) {
     if (pthread_join(tid_sistema[i], (void *) &soma_retorno_threads)) {
        printf("--ERRO: pthread_join()\n"); exit(-1);
     }
     soma_par_global += *soma_retorno_threads;
     free(soma_retorno_threads);
  }

   //imprime os resultados
   printf("\n");
   printf("\nProduto vetorial concorrente             = %.26f\n", soma_par_global);
   ret = fread(&prod_ori, sizeof(double), 1, arq); 
   printf("\nProduto vetorial sequencial                 = %.26lf\n", prod_ori);
   printf("\nVariacao dos programas                    = %.26lf\n",varRel(prod_ori,soma_par_global));
   //desaloca os espacos de memoria
   free(vet);
   free(vetb);
   free(tid_sistema);
   //fecha o arquivo
   fclose(arq);
   return 0;
}
