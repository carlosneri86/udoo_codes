#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 

/* port and server IP */
#define DESTPORT     1031
#define DESTIP       "127.0.0.1"

int main (void)
{
    int32_t SocketServer;
    struct sockaddr_in * SocketSettings;
    int32_t Status;
    int8_t * EchoBuffer;
    int32_t EchoInputSize;
    int32_t EchoReceivedSize;
    int8_t * EchoReceivedBuffer;

    /* Create our socket */
    SocketServer = socket(AF_INET, SOCK_STREAM, 0);

    if(SocketServer < 0)
    {
        printf("There was an error trying to create the socket.\n");  
        return -1;
    }
   
    SocketSettings = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));

    /* set server settings */   
    SocketSettings->sin_family = AF_INET;
    SocketSettings->sin_port = htons (DESTPORT);
    SocketSettings->sin_addr.s_addr = inet_addr(DESTIP);

    /*Try to connect the socket for the communication*/
    Status = connect(SocketServer, (struct sockaddr *)SocketSettings,sizeof(struct sockaddr));

    if(Status < 0)
    {
        printf("There was an error trying to connect the socket.\n");
        return -1;
    }
    else
    {
        printf("Server connected \n");
        EchoBuffer = (int8_t *)malloc(200);
        EchoReceivedBuffer = (int8_t *)malloc(200);
    }

    while(1)
    {
        memset(EchoBuffer,0,200);
        memset(EchoReceivedBuffer,0,200);

        fgets((char *)EchoBuffer,200,stdin);
        EchoInputSize = strlen((char *)EchoBuffer);
        (void)write(SocketServer,EchoBuffer,EchoInputSize);

        EchoReceivedSize = read(SocketServer,EchoReceivedBuffer,200);
        if(EchoReceivedSize > 0)
        {    
            printf("Received %d characters\nString received:%s\n",EchoReceivedSize,EchoReceivedBuffer);
        }
        else
        {
            printf("\nConnection to server lost\nClosing...\n");
            fflush(stdout);
            free(SocketSettings);
            free(EchoReceivedBuffer);
            free(EchoBuffer);
            close(SocketServer);

            return -1;
        }
        
    }

    /* close connection and leave */
    free(SocketSettings);
    close(SocketServer);

    return 0;
}