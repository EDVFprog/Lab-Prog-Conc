//Programa concorrente utilizando o padrão leitor e escritor

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// Criando as operações de entrada e saída para leitura e escrita
int escr,leit,querEscrever,querLer;
pthread_mutex_t mutex;
pthread_cond_t cond_escr,cond_leit;
void EntraLeitura() {
    pthread_mutex_lock(&mutex);
    querLer++;
    while(escr > 0 || querEscrever!=0 ) {
        printf("Há escritor(es)  escrevendo no momento espere...\n");
        printf("Há %d leitores na fila...\n",querLer);
        pthread_cond_wait(&cond_leit, &mutex);
        
    }
    querLer--;
    printf("Entrou um leitor ...\n");
    leit++;
    pthread_mutex_unlock(&mutex);
}
void SaiLeitura() {
    pthread_mutex_lock(&mutex);
     printf("Saiu um leitor.\n");
    printf("Há %d leitor(es) na fila \n", querLer);
    leit--;
   pthread_cond_broadcast(&cond_escr);
    pthread_mutex_unlock(&mutex);
}
void EntraEscrita () {
    pthread_mutex_lock(&mutex);
    querEscrever++;
    while((leit>0) || (escr>0)) {
    printf("Há leitor(es) %d e escritor(es) %d espere...\n",leit,escr);
    pthread_cond_wait(&cond_escr, &mutex);
}
    escr++;
    printf("Entrou um escritor ...\n");
    querEscrever--;
    pthread_mutex_unlock(&mutex);
}
void SaiEscrita () {
    pthread_mutex_lock(&mutex); 
     printf("Escritor saindo.\n");
    printf("Há %d escritor(es) na fila \n", querEscrever);
    escr--;
    pthread_cond_broadcast(&cond_escr);
    pthread_cond_broadcast(&cond_leit);
    pthread_mutex_unlock(&mutex);
}
