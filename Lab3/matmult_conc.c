/* Multiplicacao de matriz-matriz de modo concorrente*/
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include "timer.h"

float *matrizA; //matriz de entrada
float *matrizB; //matriz de entrada
float *saida; //matriz de saída
int nthreads; //numero de threads
int linhasA, colunasA; //dimensoes da matriz A
int linhasB, colunasB; //dimensoes da matriz B
typedef struct{
   int id; //identificador do elemento que a thread ira processar
  int start_row;
    int end_row;
} tArgs;

//funcao que as threads executarao
void * mult(void *arg) {
   tArgs *args = (tArgs*) arg;
     if(colunasA!= linhasB){
        printf("As matrizes não podem ser multiplicadas erro de dimensão.");
        }
  
    
     else{

     
      
    
     for (int i = args->start_row; i < args->end_row; i++) {
        for (int j=0; j<colunasB; j++) {
            for (int k =0; k<colunasA; k++) {
                saida[i*colunasB+j] += matrizA[i*colunasA + k] * matrizB[k*colunasB+j];
                
            }
        }
   
    }
   
 
}

  pthread_exit(NULL); 
  
  }


   
//fluxo principal
int main(int argc, char* argv[]) {
   
   
   long long int tamA,tamB; //qtde de elementos na matriz A e B
   FILE * arqA, *arqB,*arqS; //descritor do arquivos de entrada e arquivo de saída
   int tam= colunasA*linhasB;
   size_t retA,retB,ret; //retorno da funcao de escrita no arquivo de saida
   pthread_t *tid; //identificadores das threads no sistema
   tArgs *args; //identificadores locais das threads e dimensao
   double inicio, fim, delta;
   GET_TIME(inicio);
   //leitura e avaliacao dos parametros de entrada
   if(argc<4) {
      printf("Digite: %s <arquivos de entrada> <arquivo de saída> <numero de threads>\n", argv[0]);
      return 1;
   }
  

   //abre o arquivo para leitura binaria de entrada da matriz A
   arqA = fopen(argv[1], "rb");
   if(!arqA) {
      fprintf(stderr, "Erro de abertura do arquivo\n");
      return 2;
   }
   //abre o arquivo para leitura binaria de entrada da matriz B
   arqB = fopen(argv[2], "rb");
   if(!arqB) {
      fprintf(stderr, "Erro de abertura do arquivo\n");
      return 2;
   }


   //le as dimensoes da matriz A
   retA = fread(&linhasA, sizeof(int), 1, arqA);
   if(!retA) {
      fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo \n");
      return 3;
   }
   retA = fread(&colunasA, sizeof(int), 1, arqA);
   if(!retA) {
      fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo \n");
      return 3;
   }
   tamA = linhasA * colunasA; //calcula a qtde de elementos da matriz A

   //aloca memoria para a matriz A
   matrizA = (float*) malloc(sizeof(float) * tamA);
   if(!matrizA) {
      fprintf(stderr, "Erro de alocao da memoria da matriz\n");
      return 3;
   }

   //carrega a matriz de elementos do tipo float do arqA
   retA = fread(matrizA, sizeof(float), tamA, arqA);
   if(retA < tamA) {
      fprintf(stderr, "Erro de leitura dos elementos da matriz\n");
      return 4;
   }
   
   //imprime a matriz na saida padrao
  /* for(int i=0; i<linhasA; i++) { 
      for(int j=0; j<colunasA; j++)
        fprintf(stdout, "%.6f ", matrizA[i*colunasA+j]);
      fprintf(stdout, "\n");
   }
  */
   //le as dimensoes da matriz B
   retB = fread(&linhasB, sizeof(int), 1, arqB);
   if(!retB) {
      fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo \n");
      return 3;
   }
   retB = fread(&colunasB, sizeof(int), 1, arqB);
   if(!retB) {
      fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo \n");
      return 3;
   }
   tamB = linhasB * colunasB; //calcula a qtde de elementos da matriz B

   //aloca memoria para a matriz B
   matrizB = (float*) malloc(sizeof(float) * tamB);
   if(!matrizB) {
      fprintf(stderr, "Erro de alocao da memoria da matriz\n");
      return 3;
   }

   //carrega a matriz de elementos do tipo float do arqB
   retB= fread(matrizB, sizeof(float), tamB, arqB);
   if(retB < tamB) {
      fprintf(stderr, "Erro de leitura dos elementos da matriz\n");
      return 4;
   }
   //imprime a matriz na saida padrao
  /* for(int i=0; i<linhasB; i++) { 
      for(int j=0; j<colunasB; j++)
        fprintf(stdout, "%.6f ", matrizA[i*colunasB+j]);
      fprintf(stdout, "\n");
   }*/
   int nthreads = atoi(argv[4]);
    int tamS =colunasA*linhasB;
    saida = (float*) malloc(sizeof(float) * tamS);
   GET_TIME(fim);
   delta = fim - inicio;
   printf("Tempo inicializacao:%lf\n", delta);

   //multiplicacao da matriz pelo vetor
   GET_TIME(inicio);
   //alocacao das estruturas
   tid = (pthread_t*) malloc(sizeof(pthread_t)*nthreads);
   if(tid==NULL) {puts("ERRO--malloc"); return 2;}
   args = (tArgs*) malloc(sizeof(tArgs)*nthreads);
   if(args==NULL) {puts("ERRO--malloc"); return 2;}
    
   //criacao das threads
    int chunk_size = linhasA / nthreads;
    for (int i = 0; i < nthreads; i++) {
        (args + i)->id = i;
        (args + i)->start_row = i * chunk_size;
        (args + i)->end_row = (i + 1) * chunk_size;
        if (i == nthreads - 1) {
            (args + i)->end_row = linhasA;
        }

        if (pthread_create(tid + i, NULL, mult, (void*)(args + i))) {
            puts("ERRO--pthread_create");
            return 3;
        }
    }
   //espera pelo termino da threads
   for(int i=0; i<nthreads; i++) {
      pthread_join(*(tid+i), NULL);
   }
   GET_TIME(fim)   
   delta = fim - inicio;
   printf("Tempo multiplicacao  (nthreads %d): %lf\n", nthreads, delta);
   

   // Imprimir a matriz resultado após todas as threads terem terminado
   /* for (int i = 0; i < linhasA; i++) {
        for (int j = 0; j < colunasB; j++) {
            printf("%.6f ", saida[i * colunasB + j]);
        }
        printf("\n");
    }*/
   //liberacao da memoria
   //escreve numero de linhas e de colunas
    GET_TIME(inicio);
   arqS = fopen(argv[3], "wb");
    if(!arqS) {
      fprintf(stderr, "Erro de abertura do arquivo\n");
      return 3;
   }
    ret = fwrite(&linhasA, sizeof(int), 1, arqS);
   ret = fwrite(&colunasB, sizeof(int), 1, arqS);
   //escreve os elementos da matriz
   ret = fwrite(saida, sizeof(float), tamS, arqS);
   free(matrizA);
   free(matrizB);
   free(saida);
   free(args);
   free(tid);
   GET_TIME(fim)   
   delta = fim - inicio;
   printf("Tempo finalizacao:%lf\n", delta);

   return 0;
}
