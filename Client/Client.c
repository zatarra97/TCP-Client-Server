#include <stdio.h>
#include <winsock.h>
#define close closesocket

int main() {
	SOCKET clientsocket;		//inizializzazione socket
    SOCKADDR_IN addr;
     short port;					//Contiente la porta di comunicazione tra Client e Server
     char messaggio[5];
     
     //Parte connessione col server:
     	WORD wVersionRequested = MAKEWORD(2,2);						//inizializzazione libreria winsock
    	WSADATA wsaData;
   		WSAStartup(wVersionRequested, &wsaData);
    	port = 4000;												//numero porta di comunicazione
    	addr.sin_family = AF_INET;
   		addr.sin_addr.s_addr = inet_addr("127.0.0.1");				//127.0.0.1 indirizzo
   		addr.sin_port = htons(port);
   		clientsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	//protocollo TCP-IP
	
	
	//SE LA CONNESSIONE AL SERVER FALLISCE ESCI DAL PROGRAMMA
    if (connect(clientsocket, (LPSOCKADDR)&addr, sizeof(addr)) < 0)	//Controlla la connessione con il server
    {
    	printf("Errore nella connessione con il Server.\nIl server potrebbe essere spento.\n\n");
    	system("pause");
    	close(clientsocket);
    	WSACleanup();
    	exit (1);																			
    }else{
    	printf("Connesso al Server.\n\n");
	}
    
    printf("Inserisci messaggio da mandare al Server:\n\n\tScrivo:");
    gets(messaggio);
    
    //Viene inviata la stringa al server:
    if(send(clientsocket,messaggio,sizeof(messaggio),0)<0)		//invia messaggio della variabile "messaggio" al server;
		printf("\n\nErrore! Messaggio non inviato.Il server potrebbe essere disconnesso.\n\n");
	else{
		printf("\n\nMessaggio inviato correttamente\n");
	}
	
	
	if(recv(clientsocket, messaggio, sizeof(messaggio),0)>0){
		printf("\nRicezione avvenuta con successo.");
		printf("\nIl Server risponde: %s\n\n", messaggio);
	}else{
		printf("\nRicezione non avvenuta, il server potrebbe essere disconnesso.\n\n");
	}
	
	system("pause");
	close(clientsocket);
    WSACleanup();
return 0;	
}
	
