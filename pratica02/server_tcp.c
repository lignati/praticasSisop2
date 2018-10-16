#include "stdlib.h"
#include "stdio.h"
#include "sys/socket.h"
#include "sys/types.h"
#include "arpa/inet.h"
#include "error.h"      
#include <string.h> 
#include <unistd.h> 
#include <pthread.h>
#include <pthread.h>  
#define NUMTHREADS 100
#define PORTNUMBER 50010
#define MAXLINE 200




struct sockaddr_in server_addr;
struct sockaddr_in client_addr;
pthread_t ListThreadConnect[NUMTHREADS];
int contConnect = 0;
int serversocket;

void * NewCliente(void *idConnect){
	//int connect;
	//memcpy(&(connect),&(idConnect),sizeof(int));
	//printf("idIN %d ---- idOUT %d",(int)idConnect, connect );
	int tamr;
	char buffer[MAXLINE];
	
	printf("Conexao estabelecida com cliente %s. \n", inet_ntoa(client_addr.sin_addr));
	//Lendo mensagem enviada pelo cliente
	fprintf(stderr, "\nID: %d\n", (int)idConnect);
	tamr = read((int)idConnect, buffer, MAXLINE);
	buffer[tamr] = '\0';	
	printf("Cliente %s enviou mensagem %s", inet_ntoa(client_addr.sin_addr), buffer);

	if(strstr(buffer, "desligar")){
		//Encerra o socket servidor 
		close(serversocket);  
		//Finaliza o servidor
		exit(0);
	}
	//Encerra a conexao com o cliente
	close((int)idConnect);
	return 0;	
}





int main(){
   int socketsize;
   int flag;

   int connectionsocket;
    
   //Criacao do socket no servidor
   printf("Iniciando o servidor. \n");
   if ((serversocket = socket(AF_INET,SOCK_STREAM,0))<0){
      perror("Erro ao criar socket do servidor: \n");
   }   

   //Configuracao do endereco do servidor que sera ligado ao socket
   //zera toda a estrutura
   memset(&server_addr, 0, sizeof(server_addr));

   //Tipo de endereco
   server_addr.sin_family = AF_INET;
   //especificacao do endereco
   server_addr.sin_addr.s_addr   = INADDR_ANY;

   //Querendo especificar manualmente um endereco pode-se usar
   //server_addr.sin_addr.s_addr   = inet_addr("127.0.0.1");

   //Numero da porta
   server_addr.sin_port   = htons(PORTNUMBER);
   //
   //memset(&(server_addr.sin_zero), '\0', sizeof(server_addr.sin_zero));

   //Ligando o endereco do servidor ao socket
   if (bind(serversocket, (struct sockaddr *)&server_addr, sizeof(struct sockaddr))<0){
      perror("Erro de ligacao de socket no servidor: \n");
   } 

   //Indica que o socket deve "escutar"
   if (listen(serversocket, 1)<0){
      perror("Erro ao inicializar a escuta do socket no servidor: \n");
   }

   printf("Servidor escutando na porta: %d .\n", PORTNUMBER);
	   
   //Servidor fica em loop para receber conexoes
   while(1){
	pthread_t threadcriaConnect;
      	socketsize = sizeof(client_addr);
      
      //Servidor aguardando por conexao
      connectionsocket = accept(serversocket, (struct sockaddr *)&client_addr, &socketsize);
	printf("%d\n", connectionsocket);
      if(connectionsocket < 0){ 
         perror("Erro ao receber pedido de conexao: \n");
      }else{
	int *newID = malloc(sizeof(int));
	memcpy(&(newID),&(connectionsocket),sizeof(int));
	sleep(1);	
	pthread_create(&threadcriaConnect, NULL, NewCliente, (int *) newID);
	sleep(1);

      }
      
   }
}




