#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <stdint.h> 
#include <stdlib.h>
#include <signal.h>

#define APPLICATION_BUFFER_SIZE	(50)


void sig_handler (int signo);


const int8_t SerialHelloWorld[] =
{
    "Hello From UART\n"
};


int32_t  SerialPort;
uint8_t * SerialBuffer;

int main (void)
{
	
    uint32_t ReadData;	
	struct termios options;
	
    printf("\nInit serial port sample code.....\n");
	/* Open the UART3 driver as read/write and non blocking*/
	SerialPort = open("/dev/ttymxc2",O_RDWR|O_NOCTTY|O_NDELAY);


	if(SerialPort  > 0)
	{
		printf("TTY opened!!\n");
		/* Configure the UART */	
		fcntl(SerialPort, F_SETFL , 0);
		/* Baudrate set to 9600 */
		tcgetattr(SerialPort,&options);
		cfsetispeed(&options,B9600);
		cfsetospeed(&options,B9600);
		/* Enable receiver */
		options.c_cflag |= (CLOCAL | CREAD);
		/* No parity, 8 bits, one stop */
		options.c_cflag &= ~PARENB;
		options.c_cflag &= ~CSTOPB;
		options.c_cflag &= ~CSIZE;
		options.c_cflag |= CS8;
		/* Set the configuration*/
		tcsetattr(SerialPort, TCSANOW, &options);

	}
	else
	{
		/* In case the UART wasn't available		*/
		/* use perror to print the issue		*/
		/* If the issue is "permission denied", then, 	*/
		/* change the ttymxc2 permissons to RW          */
		/* and then try again				*/	
		perror("Serial");
		return(-1);
	}

    /* If the user presses ctrl+C this handler will be called */  
    signal(SIGINT,sig_handler);
    
	SerialBuffer = (uint8_t*)malloc(APPLICATION_BUFFER_SIZE); 
		
	printf("Starting Echo...\n");		
    (void)write(SerialPort,SerialHelloWorld,16);

    while(1)
	{
		
		ReadData = read(SerialPort,SerialBuffer,APPLICATION_BUFFER_SIZE);
        printf("Received Data %d bytes, sending it back\n",ReadData);
		if(ReadData < 0)
		{
			perror("SerialRead");
		}
		else
		{
			(void)write(SerialPort,SerialBuffer,ReadData);
		}

		memset(SerialBuffer,0,ReadData);
	}

	close(SerialPort);
	free(SerialBuffer);

	return(1);

}

void sig_handler (int signo)
{

    /* if the application is closing, free resources */
    if(signo == SIGINT)
    {
        printf("Received SIGINT: Freeing resources....\n");

        close(SerialPort);
        free(SerialBuffer);

        exit(0);

    }
}