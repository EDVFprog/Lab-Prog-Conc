/* Multiplicacao de matriz-matriz */
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>



float* multMat(int linhasA, int colunasA, float *matrizA, int linhasB, int colunasB,float* matrizB){
  int tamS =colunasA*linhasB;
     float * result = (float*) malloc(sizeof(float) * tamS);
     if(colunasA!= linhasB){
        printf("As matrizes não podem ser multiplicadas erro de dimensão.");
        }
     else{

     printf("Resultante \n");
      

     for(int i=0; i<linhasA;i++){
   
        for (int j=0;j<colunasB;j++){
          float soma=0.0;
         for (int k =0;k<colunasA; k++){
        
            
           result[i*colunasB+j]+=  matrizA[i*colunasA + k] * matrizB[k*colunasB+j];
            
            
            }
           
 }

}
  
 }
    
     
return result;

}

int main(int argc, char* argv[]) {
    float *matrizA; //matriz que será carregada do arquivo matriz A
   int linhasA, colunasA; //dimensoes da matriz A
   float *matrizB;// matriz que será carregada do arquivo matriz B
    int linhasB, colunasB; //dimensoes da matriz B
   long long int tamA,tamB; //qtde de elementos na matriz A e B
   FILE * arqA, *arqB,*arqS; //descritor do arquivos de entrada e arquivo de saída
   int tam= colunasA*linhasB;
   size_t retA,retB,ret; //retorno da funcao de escrita no arquivo de saida
   
   //recebe os argumentos de entrada
   if(argc < 3) {
      fprintf(stderr, "Digite: %s <arquivos de entrada> e <arquivo de saída> \n", argv[0]);
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
   for(int i=0; i<linhasA; i++) { 
      for(int j=0; j<colunasA; j++)
        fprintf(stdout, "%.6f ", matrizA[i*colunasA+j]);
      fprintf(stdout, "\n");
   }
  
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

   //carrega a matriz de elementos do tipo float do arqA
   retB= fread(matrizB, sizeof(float), tamB, arqB);
   if(retB < tamB) {
      fprintf(stderr, "Erro de leitura dos elementos da matriz\n");
      return 4;
   }
      printf("\n");
 
 //imprime a matriz de entrada B
   for(int i=0; i<linhasB; i++) { 
      for(int j=0; j<colunasB; j++)
        fprintf(stdout, "%.6f ", matrizB[i*colunasB+j]);
      fprintf(stdout, "\n");
   }

   float *M =multMat( linhasA,  colunasA,  matrizA,  linhasB,  colunasB, matrizB);
   //imprime a matriz na saida padrao
    for(int i=0; i<linhasA; i++) { 
      for(int j=0; j<colunasB; j++)
        fprintf(stdout, "%.6f ", M[i*colunasB+j]);
      fprintf(stdout, "\n");
   }
   // escreve a matriz de saída e suas dimensões no arquivo binário de saída
   //abre o arquivo para escrita binaria
   arqS = fopen(argv[3], "wb");
   if(!arqS) {
      fprintf(stderr, "Erro de abertura do arquivo\n");
      return 3;
   }
    //escreve numero de linhas e de colunas
    ret = fwrite(&linhasA, sizeof(int), 1, arqS);
   ret = fwrite(&colunasB, sizeof(int), 1, arqS);
   //escreve os elementos da matriz
   ret = fwrite(M, sizeof(float), tam, arqS);
    //finaliza o uso das variaveis
   fclose(arqA);
   free(matrizA);
   fclose(arqB);
   free(matrizB);
   fclose(arqS);
   free(M);
   return 0;
}
