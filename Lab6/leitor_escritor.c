//Programa concorrente utilizando o padrão leitor e escritor

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// variáveis de controle para leitura e escrita na fila de leitores e escritores
int escr,leit,querEscrever,querLer;
// controle por exclusão mútua e sincronização da var condicional para leitura e escrita
pthread_mutex_t mutex;
pthread_cond_t cond_escr,cond_leit;
// Criando as operações de entrada e saída para leitura e escrita
void EntraLeitura() {
    pthread_mutex_lock(&mutex);
    // Assim que entramos na leitura incrementamos a var querLer pois há um leitor querendo realizar operação porém precisamos avaliar se podemos ler ou não
    querLer++;
    // Se existir algum escritor escrevendo no momento ou um escritor querendo entrar para escrever  o leitor deve esperar até que a escrita seja realizada
    while(escr > 0 || querEscrever!=0 ) {
        printf("Há escritor(es)  escrevendo no momento espere...\n");
        pthread_cond_wait(&cond_leit, &mutex);
        
    }
    // A variável quer ler é decrementada pois o leitor está realizando  a leitura, e assim incrementamos o número de leitores tendo em vista que podem haver leituras simultâneas
    querLer--;
    printf("Entrou um leitor ...\n");
    leit++;
    pthread_mutex_unlock(&mutex);
}
void SaiLeitura() {
    // Marca a saída do leitor com um log e outro para mostrar a quantidade de leitores que ainda querem ler além disso decrementa a quantidade de leitores. Desbloqueando todas as threads que foram bloqueadas na fila dos escritores
    pthread_mutex_lock(&mutex);
     printf("Saiu um leitor\n");
     leit--;
    printf("Há %d leitor(es) na fila \n", querLer);
   pthread_cond_broadcast(&cond_escr);
    pthread_mutex_unlock(&mutex);
}
void EntraEscrita () {
    pthread_mutex_lock(&mutex);
     // Assim que entramos na escrita incrementamos a var querEscrever pois há um escritor querendo realizar operação porém precisamos avaliar se podemos escrever ou não
    querEscrever++;
     // Se existir algum leitor lendo no momento ou um escritor querendo escrever, o escritor que deseja escrever deve esperar até que as operações sejam realizadas.
    while((leit>0) || (escr>0)) {
    printf("Há leitor(es) %d e escritor(es) %d espere...\n",leit,escr);
    pthread_cond_wait(&cond_escr, &mutex);
} // A variavel querEscrever  é decrementada pois o escritor está realizando a escrita, e assim incrementamos o número de escritores 
    escr++;
    printf("Entrou um escritor ...\n");
    querEscrever--;
    pthread_mutex_unlock(&mutex);
}
void SaiEscrita () {
     // Marca a saída de um escritor com um log e outro para mostrar se há escritores que ainda querem escrever.Além disso decrementa a quantidade de escritores pois estamos saindo da escrita
    // Desbloqueia todas as threads que foram bloqueadas na fila dos escritores e da fila de leitores para que o próximo leitor leia ou caso haja escritores na fila os mesmos escrevam antes que 
    // os leitores iniciem sua operação 
    pthread_mutex_lock(&mutex); 
     printf("Escritor saindo.\n");
    printf("Há %d escritor(es) na fila \n", querEscrever);
    escr--;
    pthread_cond_broadcast(&cond_escr);
    pthread_cond_broadcast(&cond_leit);
    pthread_mutex_unlock(&mutex);
}
