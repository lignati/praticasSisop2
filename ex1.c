#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#define NUM_THREADS 5
void *printNomeThread(void * ptr);

// extern int pthread_create(pthread_t * thread, attributes * attr, void * (*function)(void *), void * arg);

int main (){
long i;
pthread_t thread[NUM_THREADS];	
	
	for (i = 0; i< NUM_THREADS; i++){
		pthread_create(&(thread[i]), NULL, printNomeThread,(void *) i);
	}
	for (i=0; i < NUM_THREADS; i++){
      pthread_join(thread[i],NULL);
	}
}



void *printNomeThread(void *  ptr){
	long numero;
	memcpy(&(numero),&(ptr),sizeof(long));
	printf("Sou a thread %ld \n",numero);

}
