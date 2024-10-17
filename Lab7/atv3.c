// Programa concorrente que le, manipula e imprime na tela os caracteres do arquivo texto de entrada.
// Importando dependencias
#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>
#include <semaphore.h>

 
#define nthreads 3 // Definindo o número de threads
#define N 500 // Definindo o tamanho do buffer e o tamanho dos blocos de leitura

// Semáforos para ao tratamento das demandas de sincronização entre as 3 threads
sem_t estado1,estado2;
// buffer globais do tamanho N definido, o segundo buffer tem o dobro do tamanho caso o seu tratamento necessite que aumente seu tamanho final por causa dos \n 
char buffer1[N];
char buffer2[2*N];

// Thread 1  - responsável pela leitura do arquivo em blocos de N e carga desses blocos no buffer1
void *t1(void *arg) 
{
    FILE *arq;
    char *arquivo = (char*) arg;// pega o arquivo como argumento
    char ch;// caracter a ser lido
    // se o arquivo não for reconhecido, printa mensagem de erro
    if((arq = fopen(arquivo,"r")) == NULL)
    {
        printf("Arquivo inválido");
        exit(1);
    }
// De N em N blocos pega o caracter ch e o coloca no buffer
for (int i = 0; i < N; i++) {
            ch = fgetc(arq); 
            if (ch == EOF) { 
                break;
            }
            buffer1[i] = ch; 
    }
    
    fclose(arq);
    sem_post(&estado1);
    pthread_exit(NULL);
}
// processamento   inserção dos caracteres no buffer1
void processamento(){
    int i = 0;  
    int j = 0;  
    int n = 0;  
    int cont = 0; 
    while(buffer1[i] != '\0') {
        buffer2[j] = buffer1[i];
        j++;
        i++;
        cont+;
         // O contador verifica se precisamos inserir os \n para o primeiro caso
        if ((cont == (2 * n + 1)) && (n<10)) {
            buffer2[j] = '\n';
            j++;
            n++;  
           cont = 0;
        }
        // Contador para inserir de 10 em 10 caracteres
        if((cont == 10) && n>=10){
            buffer2[j] = '\n';
            j++;
            n++;  
            cont = 0;
        }
    }
 // final do buffer2
    buffer2[j] = '\0';

}
// Thread 2  - responsável pelo processamento do buffer1 para o buffer conforme explicitado no enuciado
void *t2(void *arg) 
{ 
    sem_wait(&estado1);
    processamento();
    sem_post(&estado2);
    
    pthread_exit(NULL);
}
// Thread 3 - printa o buffer2
void *t3(void *arg)
{
    sem_wait(&estado2);
    for(int i=0; i<N;i++){
     printf("%c",buffer2[i]);
    }
   
    pthread_exit(NULL);
}


int main(int argc, char *argv[])
{
    pthread_t tid[nthreads];
    if(argc < 2)
    {
        puts("Digite: %s <nome do arquivo>");
        exit(1);
    }
    
    sem_init(&estado1,0,0);
    sem_init(&estado2,0,0);



     //cria as tres threads
  if (pthread_create(&tid[2], NULL, t3, NULL)) { 
	  printf("--ERRO: pthread_create()\n"); exit(-1); }
  if (pthread_create(&tid[1], NULL, t2, NULL)) { 
	  printf("--ERRO: pthread_create()\n"); exit(-1); }
  if (pthread_create(&tid[0], NULL, t1, (void *) argv[1])) { 
	  printf("--ERRO: pthread_create()\n"); exit(-1); }

  //--espera todas as threads terminarem
  for (int t=0; t<nthreads; t++) {
    if (pthread_join(tid[t], NULL)) {
         printf("--ERRO: pthread_join() \n"); exit(-1); 
    } 
  } 
   
    sem_destroy(&estado1);
    sem_destroy(&estado2);

    return 0;
}
