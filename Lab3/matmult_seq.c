/* Multiplicacao de matriz-matriz de modo concorrente */
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include "timer.h"


//funcao que as threads executarao
void * tarefa(void *arg) {
   tArgs *args = (tArgs*) arg;
   for(int i=args->id; i<args->dim; i+=nthreads)
      for(int j=0; j<args->dim; j++) 
         saida[i] += mat[i*(args->dim) + j] * vet[j];
   pthread_exit(NULL);
}

//fluxo principal
int main(int argc, char* argv[]) {
   double inicio, fim, delta;
   float *matrizA; //matriz que será carregada do arquivo a
   int linhasA, colunasA; //dimensoes da matriz a
   float *matrizB; //matriz que será carregada do arquivo b
   int linhasB, colunasB; //dimensoes da matriz b
   long long int tam; //qtde de elementos na matriz
   FILE * arqA; //descritor do arquivo de entrada da matriz A
   FILE * arqB; //descritor do arquivo de entrada da matriz B
   FILE *arqS;// arquivo de saida
   size_t ret; //retorno da funcao de leitura no arquivo de entrada
   GET_TIME(inicio);
   //leitura e avaliacao dos parametros de entrada
   if(argc<4) {
      printf("Digite: %s <os arquivos de entrada> <arquivo de saida>\n", argv[0]);
      return 1;
   }
  //abre o arquivo para leitura binaria matriz A
   arqA= fopen(argv[1], "rb");
   if(!arqA) {
      fprintf(stderr, "Erro de abertura do arquivo\n");
      return 2;
   }
    //abre o arquivo para leitura binaria matriz B
   arqA= fopen(argv[2], "rb");
   if(!arqB) {
      fprintf(stderr, "Erro de abertura do arquivo\n");
      return 2;
   }

   //le as dimensoes da matriz
   ret = fread(&linhasA, sizeof(int), 1,arqvA);
   if(!ret) {
      fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo \n");
      return 3;
   }
   ret = fread(&colunas, sizeof(int), 1, descritorArquivo);
   if(!ret) {
      fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo \n");
      return 3;
   }
   tam = linhas * colunas; //calcula a qtde de elementos da matriz

   //aloca memoria para a matriz
   matriz = (float*) malloc(sizeof(float) * tam);
   if(!matriz) {
      fprintf(stderr, "Erro de alocao da memoria da matriz\n");
      return 3;
   }

   //carrega a matriz de elementos do tipo float do arquivo
   ret = fread(matriz, sizeof(float), tam, descritorArquivo);
   if(ret < tam) {
      fprintf(stderr, "Erro de leitura dos elementos da matriz\n");
      return 4;
   }

   //imprime a matriz na saida padrao
   for(int i=0; i<linhas; i++) { 
      for(int j=0; j<colunas; j++)
        fprintf(stdout, "%.6f ", matriz[i*colunas+j]);
      fprintf(stdout, "\n");
   }

   //finaliza o uso das variaveis
   fclose(descritorArquivo);
   free(matriz);

   return 0;
}
