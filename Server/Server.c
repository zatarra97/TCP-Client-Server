#include <stdio.h>
#include <winsock.h>
#include <string.h>
#define close closesocket

int main() {
	
	int sin_size;
	short port;
	char codice[10];	//Contiene il messaggio per i client
	int ls_result;
	int wsastartup;	
    SOCKET listenSocket;
	SOCKET remoteSocket;
	SOCKADDR_IN Server_addr;
	SOCKADDR_IN Client_addr;
	
	
	 /* Inizializzazione della libreria Socket */
		    WORD wVersionRequested = MAKEWORD(2,2);
		    WSADATA wsaData;
		    wsastartup = WSAStartup(wVersionRequested, &wsaData);
		    if (wsastartup != NO_ERROR) printf("Errore WSAStartup()\n");

		    /* Creazione della Socket che si porrà in ascolto di richieste del Client*/
		    listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		    if (listenSocket < 0)
		    printf("Server: errore nella creazione della socket.\n");

		    /* Effettua la bind sull’indirizzo e porta ora specificati */
		    port = 4000;
		    Server_addr.sin_family = AF_INET;
		    Server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
		    Server_addr.sin_port = htons(port);

		    if (bind(listenSocket,(LPSOCKADDR)&Server_addr,sizeof(struct sockaddr)) < 0)
		    printf("Server: errore durante la bind.\n");
		    printf("In attesa che un client si connetta...\n");
		    
		    /* La socket si pone in "ascolto" tramite la listen() */
		    ls_result = listen(listenSocket, SOMAXCONN);

		    if (ls_result < 0) printf("Server: errore durante la listen.\n");
		    /* La socket accetta la richiesta di connessione del Client */
		    sin_size = sizeof(struct sockaddr_in);
		    remoteSocket = accept(listenSocket, (struct sockaddr *)&Client_addr, &sin_size);
		    printf("Client Connesso!\n");
		    
		    
		    /* Il Server riceve il messaggio dal Client */
		    if(recv(remoteSocket, codice, sizeof(codice) , 0)>0){
		    	printf("\nRicezione avvenuta con Successo\n\n");
				printf("%s", codice);	
			}else{
				printf("\nAttenzione, ricezione non avvenuta, assicurarsi che il client sia connesso.\n\n");
			}
			
			strcpy(codice, "ciao");
			if(send(remoteSocket, codice,sizeof(codice),0)>0)			//invia messaggio al client
    			printf("\n\tMessaggio inviato correttamente al client\n");
		    else
		    {
		    	printf("\n\tErrore! Il messaggio non e' stato inviato. \n\tIl client potrebbe essere disconnesso.\n");
			}
			
			system("pause");
			close(remoteSocket);
		    WSACleanup();
	return 0;
}
