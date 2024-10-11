// Implementacao padrão leitor escritor usando semáforos.
#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>
#include <semaphore.h>
sem_t slotCheio,slotVazio;// condições para verificar o buffer
sem_t mutexProd,mutexCons;//exclusão mutua (mutex implementado com o semaforo)
#define N 5
#define NTHREADS 3
char buffer1[N];
char buffer2[2*N];

void Insere(int item){
	static int in=0;
	sem_wait(&slotVazio);
	sem_wait(&mutexProd);
	buffer1[in] = item;
	in = (in+1)%N;
	sem_post(&mutexProd);
	sem_post(&slotCheio);
}
char Retira () {
	int item;
	static int out=0;
	//aguarda slot cheio
	sem_wait(&slotCheio);
	//exclusao mutua entre consumidores
	sem_wait(&mutexCons);
	item = buffer1[out];
	out = (out + 1) % N;
	sem_post(&mutexCons);
	//sinaliza um slot vazio
	sem_post(&slotVazio);
	return item;
	}

//funcao executada pela thread 1
void *t1 (void *arg) {
char *arquivo= (char *)arg;
FILE *fp;
char ch;
 fp = fopen(arquivo, "r");
    if (fp == NULL) {
        perror("Erro ao abrir o arquivo");
        pthread_exit(NULL);
    }
    // A ideia é inserir em blocos de N
while ((ch = fgetc(fp)) != EOF) {
Insere(ch);
}
printf("%s", buffer1);
fclose(fp);
pthread_exit(NULL);

}
//funcao executada pela thread 2
//void *t2 (void *arg) {
//for (int i ; i<N;i++){
//int n =0;
 // Processar os caracteres
 // n sei como fazer essa área ainda
//for (int j = 0; j < count; j++) {
  //Insere(buffer[j],buffer2);
    //if ((n < N && (j+1) % (2*n+1) == 0) || (n >= N && (j+1) % 10 == 0)) {
      //          buffer2[i++] = '\n';
        //        n++;
          //  }
        //}

//}
//pthread_exit(NULL);
//}
//void *t3(void *arg){
//char elemento = Retira();
//printf("%c", elemento);
//}
//funcao principal
int main(int argc, char *argv[]) {
  pthread_t tid[NTHREADS];
  sem_init(&mutexCons,0,1);
  sem_init(&mutexProd,0,1);
  sem_init(&slotCheio,0,0);
  sem_init(&slotVazio,0,N);
 // O nome do arquivo e o tamanho do buffer devem ser definidos 
   if(argc<2) {
      printf("Digite: %s <nome do arquivo>\n", argv[0]);
      return 1;
   }
  char * arquivo = argv[1];
  //cria as tres threads
   if (pthread_create(&tid[0], NULL, t1, (void *)arquivo)) { 
	  printf("--ERRO: pthread_create()\n"); exit(-1); }
  //if (pthread_create(&tid[2], NULL, t3, NULL)) { 
	// printf("--ERRO: pthread_create()\n"); exit(-1); }
  //if (pthread_create(&tid[1], NULL, t2, NULL)) { 
	  //printf("--ERRO: pthread_create()\n"); exit(-1); }
 

  //--espera todas as threads terminarem
  for (int t=0; t<NTHREADS; t++) {
    if (pthread_join(tid[t], NULL)) {
         printf("--ERRO: pthread_join() \n"); exit(-1); 
    } 
  } 
 
  sem_destroy(&mutexCons);
  sem_destroy(&mutexProd);
  sem_destroy(&slotCheio);
  sem_destroy(&slotVazio);
  return 0;
}
