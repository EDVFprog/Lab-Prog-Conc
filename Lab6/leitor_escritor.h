//Programa concorrente define as funções utilizadas no padrão leitor e escritor

#include <stdio.h>
#include <stdlib.h>
int escr =0,leit=0,querEscrever=0,querLer=0;
pthread_mutex_t mutex;
pthread_cond_t cond_escr,cond_leit;
void EntraLeitura();
void SaiLeitura() ;

void EntraEscrita () ;

void SaiEscrita () ;
