#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <time.h>
#include <unistd.h>
#define NUM_OPS 2
#define NUM_ESCRITORES 3
#define NUM_LEITORES 3

//inicia o saldo
int saldo = 0;

//inicia a variavel que conta o numero de leitores lendo
int numero_leitores=0;

//semaforo para garantir exclusao mutua no acesso a variavel numero_leitores
sem_t sema_num_l;

//semaforo para garantir exclusao mutua no acesso a variavel saldo
sem_t sema_saldo;

// variavel para manter leitores vivos
int finaliza = 1;

void *escritor(void *);
void *leitor(void *);
void *crialeitor(void *);
void *criaescritor(void *);

int main(){
   int i;

   //declaracao das threads de criacao
   pthread_t threadcrials;
   pthread_t threadcriaes;


   //inicializacao dos semaforos
   sem_init(&sema_num_l, 0, 1);
   sem_init(&sema_saldo, 0, 1);
 
   //inicializacao da thread que cria threads escritores
   pthread_create(&threadcriaes, NULL, criaescritor, NULL);

   //inicializacao da thread que cria threads leitores
   pthread_create(&threadcrials, NULL, crialeitor, NULL);
   
   //join das threads de criacao
   pthread_join(threadcriaes, NULL);   
   finaliza = 0;
   pthread_join(threadcrials, NULL);   
   
   printf("Saldo final na conta = %d \n", saldo);
}

//funcao que sera executada pelas threads escritor
void *escritor(void * id){
   int novo_saldo;
   int idp = (int)*(int *)id;
   printf("Escritor %d aguardando acesso. \n" , (int)*(int *)id );
   sem_wait(&sema_saldo);
      printf("Iniciando alteracao. Escritor %d \n", (int)*(int *)id );
      novo_saldo = saldo + (10 * idp);
      usleep(2);
      saldo = novo_saldo;
      printf("Alteracao Finalizada.%d \n", (int)*(int *)id);
   sem_post(&sema_saldo);
}

//funcao que sera executada pelas threads leitor
//somente esta funcao necessita ser alterada no exercicio 3
void *leitor(void * id){


//O que fazer:
//Todas as variaveis e semaforos necessarios ja estao criados. Somente 1 leitor/escritor deve acessar ae secoes criticas por vez.
//Voce tem apenas que inserir na posicao correta os semaforos e as variaveis para garantir a solucao do problema apresentado em aula
//Variaveis que devem ser utilizadas aqui:
//    numero_leitores
//Semaforos que devem ser utilizados:
//   sema_num_l
//   sema_saldo
   
      
          sem_wait(&sema_num_l);
		  printf("	Entrei na fila %d\n",(int)*(int *)id);
		  if(numero_leitores == 0){
			printf("inicializa fila de leitores leitor %d\n",(int)*(int *)id);
			sem_wait(&sema_saldo);
		  }
		  numero_leitores++;
	  sem_post(&sema_num_l);
   
	


     printf("		Leitor %d leu saldo = %d. \n", (int)*(int *)id , saldo);
     usleep(1);
	  sem_wait(&sema_num_l);
		  numero_leitores--;
		  
		  if(numero_leitores == 0){
			printf("fila vazia leitor %d\n",(int)*(int *)id);
			sem_post(&sema_saldo);
		  }
	  sem_post(&sema_num_l);	
     	  printf("	sai da fila leitor %d\n",(int)*(int *)id);
     
}

//funcao que sera executada pelas threads leitor
void *criaescritor(void * id){
   int i;
   int nops = NUM_OPS;
   
   
  
   //declaracao das threads leitores
   pthread_t threadse[NUM_ESCRITORES];
   
   while(nops > 0){
      //inicializacao das threads leitores
      for (i=0; i < NUM_ESCRITORES; i++){
        int *  temp;
	temp = malloc(sizeof(int));
	*temp  = i;
         pthread_create(&threadse[i], NULL, escritor, (void*) temp );
       //  printf("Iniciando escritor %d id = %d . \n", *(&i), &id );
      }
 
      for (i=0; i < NUM_ESCRITORES; i++){
         pthread_join(threadse[i], NULL);
      }
      usleep(1);
      nops--;
   }
}


//funcao que sera executada pelas threads leitor
void *crialeitor(void * id){
   int i;
   
   
   //declaracao das threads leitores
   pthread_t threadsl[NUM_LEITORES];
   
   while(finaliza){
      //inicializacao das threads leitores
      for (i=0; i < NUM_LEITORES; i++){
	int *  temp;
	temp = malloc(sizeof(int));
	*temp  = i;
         pthread_create(&threadsl[i], NULL, leitor, (void*) temp );
      //   printf("Iniciando leitor %d, id = %d. \n",  *(&i), *(&id));
      }
 
      for (i=0; i < NUM_LEITORES; i++){
         pthread_join(threadsl[i], NULL);
      }
      usleep(1);
   }
}

