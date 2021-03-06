#include <stdio.h> 
#include <sys/socket.h>		
#include <arpa/inet.h>         
#include <string.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <error.h>            
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAXLINE 200



int main(){
	
   int clientSock;
   int conn;
   unsigned int tams;
   char buffer[MAXLINE];
   struct sockaddr_in s;
   int portaServidor = 50010;
   char resource[5][255] = {"Impressora01\n", "Impressora02\n", "Impressora03\n", "Míssil01\n", "Míssil02\n" };
   int maxResouce = 4;
   char message[255];   

   //Criando socket cliente
   clientSock = socket(AF_INET, SOCK_STREAM, 0);
   if(clientSock < 0){ 
		perror("Erro na criacao do socket client: ");
   }
	
   memset(&s, 0, sizeof(s));
   
   //Especificacao do endereco do servidor para efetuar conexao
   s.sin_family = AF_INET;
   s.sin_addr.s_addr = inet_addr("127.0.0.1");
   s.sin_port = htons(portaServidor);        
	
   //Efetua conexao com o sevidor
   conn = connect(clientSock, (struct sockaddr *) &s, sizeof(s));
   if(conn < 0){
      perror("Erro ao tentar se conectar com o servidor: ");
   }

    srand((int)time(NULL));
    char resourceSelect[255];
    strcpy(resourceSelect, resource[rand()%maxResouce]) ;
    printf("Recurso: --> %s", resourceSelect);
    strcat(resourceSelect, itoa(clientSock));
     
   //Envia mensagem ao servidor 
   tams = write(clientSock,resourceSelect,strlen(resourceSelect));
   if(tams == strlen(resourceSelect)){
      printf("Mensagem enviada. \n");
      
   }else{
	printf("Erro no servidor.\n");
   }
   
   conn = close(clientSock);
   printf("Cliente ecerrado. \n");
   exit(0);
}
