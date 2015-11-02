#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>	// this includes the "sockaddr_in" structure
#include <errno.h>
#include <stddef.h>
#include <wchar.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdint.h>

/* Defines the port to be used */
#define PORT_NUM	(1030)


int main (void)
{
	int32_t ListenSocket;
	struct sockaddr_in *SocketSettings;
	struct sockaddr_in *ClientSocketSettings;
	int32_t ErrorChecking = 0;
	int32_t ClientSocket;
	
	socklen_t ClientSocketSettingsSize = sizeof(struct sockaddr_in);	

	
	/* Create the server project*/
	ListenSocket = socket(AF_INET,SOCK_STREAM,0);

    /* just in case the socket failed */
	if(ListenSocket < 0) 
	{

		printf("Error creating socket\n");
		return(-1);
	}


	/* Create the socket settings and configure */
	SocketSettings = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));
	
	SocketSettings->sin_family = AF_INET;
	SocketSettings->sin_addr.s_addr = INADDR_ANY;
	SocketSettings->sin_port = htons(PORT_NUM);

	/* Bind the socket to the settings */
	ErrorChecking = bind(ListenSocket, (struct sockaddr*)SocketSettings,sizeof(struct sockaddr_in));

	if(ErrorChecking  < 0)
	{

		printf("Error binding socker \n");
		return (-1);

	}

	/* Set the socket to listen mode*/
	listen(ListenSocket, 0);

	printf("Waiting for a client...\n");


	/* Create the client socket settings */
	ClientSocketSettings = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));


	/* Accept incoming connections */
	ClientSocket = accept(ListenSocket, (struct sockaddr*)ClientSocketSettings,&ClientSocketSettingsSize);

	
	
	printf("Client Accepted!!\n");
	
	/* Close both sockets and exit */
	close(ListenSocket);
	close(ClientSocket);

	free(SocketSettings);
	free(ClientSocketSettings);

	return(0);


}
