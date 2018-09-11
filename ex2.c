#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <pthread.h>
#include <semaphore.h>


#define NUMOPER 10
#define NUMTHREADS 3
//inicia o saldo
int saldo = 100;

void creditar(int valor);
void debitar(int valor);
void *threadcreditar(void *);
void *threaddebitar(void *);

sem_t mutex;

int main(){
   //declara&ccedil;&atilde;o das threads que fazem d&eacute;bitos
   pthread_t threadsd[NUMTHREADS];
   //declara&ccedil;&atilde;o das threads que fazem cr&eacute;ditos
   pthread_t threadsc[NUMTHREADS];
   
   
   sem_init (&mutex, 0, 1);
   
   int i;
   
   //inicializa&ccedil;&atilde;o das threads
   for (i=0; i<NUMTHREADS; i++){
      pthread_create(&threadsc[i], NULL, threadcreditar, NULL);
      pthread_create(&threadsd[i], NULL, threaddebitar, NULL);
   }

   //join das threads (sincroniza&ccedil;&atilde;o com a thread principal)
   for (i=0; i<NUMTHREADS; i++){
      pthread_join(threadsc[i],NULL);
      pthread_join(threadsd[i],NULL);
   }
    sem_destroy (&mutex);
   printf("Saldo final na conta = %d \n", saldo);
}


//procedimento que efetua cr&eacute;ditos na conta(saldo)
void creditar(int valor){
	 sem_wait(&mutex);
   int saldo_conta = saldo + valor;
   printf("Creditando valor. \n");
   printf("O novo valor sera %d. \n", saldo_conta);
//   sleep(1);

   saldo = saldo_conta;
   sem_post(&mutex);
}

//procedimento que efetua d&eacute;bitos na conta(saldo)
void debitar(int valor){
	sem_wait(&mutex);
   int saldo_conta = saldo - valor;
   printf("Debitando valor. \n");
   printf("O novo valor sera %d. \n", saldo_conta);
//   sleep(1);

   saldo = saldo_conta;
   sem_post(&mutex);
}

//fun&ccedil;&atilde;o que ser&aacute; executada pelas threads tipo threadsc
void * threadcreditar(void *dummy){
   int i;
   for (i=0;i<NUMOPER;i++){
      creditar(100);
   }
}

//fun&ccedil;&atilde;o que ser&aacute; executada pelas threads tipo threadsd
void * threaddebitar(void *dummy){
   int i;
   for (i=0;i<NUMOPER;i++){
      debitar(100);
   }
}

