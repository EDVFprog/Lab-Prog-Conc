/* Disciplina: Computacao Concorrente */
/* Aluna.: Eduarda Varela Fahr */
/* Lab2:  */
/* Codigo: Realiza o produto entre 2 vetores de tamanho N de modo sequencial */

#include <stdio.h>
#include <stdlib.h> 

//variaveis globais
//tamanho do vetor
long int n;
//vetor de elementos
float *vet;
// vetorb
float *vetb;

double prodVet(float *vet1,float *vet2,long int N){
double soma=0.0;
for(int i=0; i<N;i++){
   soma+=vet1[i]*vet2[i];
}
return soma;
}
int main(int argc, char *argv[]) {
 FILE *arq; //arquivo de entrada
  size_t ret; //retorno da funcao de leitura no arquivo de entrada
  //valida e recebe os valores de entrada
  if(argc < 2) { printf("Use: %s <arquivo de entrada> \n", argv[0]); exit(-1); }
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
  if(ret < n) {
     fprintf(stderr, "Erro de leitura dos elementos do vetor\n");
     return 4;
  }
   //aloca espaco de memoria e carrega o vetor de entrada
  vetb = malloc (sizeof(float) * n);
  if(vetb==NULL) { printf("--ERRO: malloc()\n"); exit(-1); }
  ret = fread(vetb, sizeof(float), n, arq);

  double prod=prodVet(vet,vetb,n);
  // Teste para ver se a soma está correta do produto
  //printf("%f",prod);
   // escrevendo os elementos do vetorb
   ret =fwrite(&prod,sizeof(double),1,arq);
   // desaloca os vetores
   free(vet);
   free(vetb);
    //fecha o arquivo
  fclose(arq);
  
  }
