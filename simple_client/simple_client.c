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
#define DESTPORT     1030
#define DESTIP       "127.0.0.1"

int main (void)
{
    int32_t SocketServer;
    struct sockaddr_in * SocketSettings;
    int32_t Status;

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
    }
   
    /* close connection and leave */
    free(SocketSettings);
    close(SocketServer);

    return 0;
}
