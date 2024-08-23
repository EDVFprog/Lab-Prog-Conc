/*
/* Disciplina: Computacao Concorrente */
/* Aluna.: Eduarda Varela Fahr */
/* Lab2:  */
/* Codigo:Gera os vetores que serão utilizados para o produto vetorial
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000 //valor maximo de um elemento do vetor
#define TEXTO // imprime os valores gerados do vetor


// calcula o produto vetorial
double prodVet(float *vet1,float *vet2,long int N){
  double soma=0.0;
  for(int i=0; i<N;i++){
    soma+=vet1[i]*vet2[i];
  }
  return soma;
}
// cria o vetor
float* criaVetor(long int n){
  float elem;
  int fator=1; 
  float* vetor = (float*)malloc(n * sizeof(float));
  //preenche o vetor com valores float aleatorios
  for(long int i=0; i<n; i++) {
        elem = (rand() % MAX)/3.0 * fator;
        vetor[i] = elem;
        
        fator*=-1;
  }
  return vetor;
}

int main(int argc, char*argv[]) {
 
   long int n; //qtde de elementos do vetor que serao gerados
   float elem; //valor gerado para incluir no vetor
   FILE * descritorArquivo; //descritor do arquivo de saida
   size_t ret; //retorno da funcao de escrita no arquivo de saida

   //recebe os argumentos de entrada
   if(argc < 3) {
      fprintf(stderr, "Digite: %s <dimensao> <arquivo saida>\n", argv[0]);
      return 1;
    }
   n = atoi(argv[1]);
   float *vetor=criaVetor(n);// criando o vetor
   float *vetorb=criaVetor(n);// cria o vetor b


   //imprimir na saida padrao o vetor gerado
   #ifdef TEXTO
   fprintf(stdout, "%ld\n", n);
   for(long int i=0; i<n; i++) {
      fprintf(stdout, "%f ",vetor[i]);
   }
   fprintf(stdout, "\n");
   for(long int i=0; i<n; i++) {
      fprintf(stdout, "%f ",vetorb[i]);
   }
   fprintf(stdout, "\n");
 #endif
   
   //abre o arquivo para escrita binaria
   descritorArquivo = fopen(argv[2], "wb");
   if(!descritorArquivo) {
      fprintf(stderr, "Erro de abertura do arquivo\n");
      return 3;
   }
   //escreve a dimensao
   ret = fwrite(&n, sizeof(long int), 1, descritorArquivo);
   //escreve os elementos do vetor
   ret = fwrite(vetor, sizeof(float), n, descritorArquivo);
   // escrevendo os elementos do vetorb
   ret =fwrite(vetorb,sizeof(float),n,descritorArquivo);
   
   if(ret < n) {
      fprintf(stderr, "Erro de escrita no  arquivo\n");
      return 4;
   }
   double prod=prodVet(vetor,vetorb,n);
   // Teste para ver se produto vetorial  está correto 
   printf("%f",prod);
   // escrevendo o resultado do produto vetorial no arquivo binario
   ret =fwrite(&prod,sizeof(double),1,descritorArquivo);
   //finaliza o uso das variaveis e fecha o arquivo
   fclose(descritorArquivo);
   free(vetor);
   free(vetorb);
   return 0;
} 
