#include <mqueue.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h> 
#include <stdint.h>
#include <stdlib.h>


#define MQ_MODE       (S_IRWXU | S_IRWXG | S_IRWXO)

#define INCREMENT_COMMAND	('i')

#define MAX_MESSAGES		(10)

#define	MAX_MESSAGES_SIZE	(10)

#define COMMAND_BUFFER_SIZE	(MAX_MESSAGES * MAX_MESSAGES_SIZE)


/*Function used for the threads*/
void *vfnThreadPrint(void *pvMessageQueue);

void *vfnThreadIncrement(void *pvMessageQueue);


int main (int argc, char *argv[])
{
	int32_t dwflags = 0;
	struct mq_attr queue_attributes;
	mqd_t mqd;
	pthread_t ThreadPrint;
	pthread_t ThreadIncrement;


	dwflags |=  O_CREAT|O_RDWR;
	queue_attributes.mq_maxmsg = MAX_MESSAGES;
	queue_attributes.mq_msgsize = MAX_MESSAGES_SIZE;
	queue_attributes.mq_flags = 0;
 
	mqd = mq_open("/Message_queue_test", dwflags, MQ_MODE,&queue_attributes);


	if(mqd < 0)
	{

		perror("MessageCreate");

	}
	/* Create independent threads each of which will execute function */

	(void)pthread_create(&ThreadPrint, NULL, &vfnThreadPrint, (void*)&mqd);
	(void)pthread_create(&ThreadIncrement, NULL, &vfnThreadIncrement, (void*)&mqd);


	while(1)
	{


	}	
}


void *vfnThreadPrint(void *pvMessageQueue)
{
	mqd_t * PrintMessageQueue = (mqd_t*)pvMessageQueue;
	char * pbCommandBuffer = (char*)malloc(COMMAND_BUFFER_SIZE);

	printf("Print Message Queue ID: %d\n", *PrintMessageQueue);
	while(1)
	{
		/* Wait for user input and send it*/
		printf("Write a command:\n");
		fgets(pbCommandBuffer,COMMAND_BUFFER_SIZE,stdin);
		/* Just the first character will be sent, hence the '1'*/
		(void)mq_send(*PrintMessageQueue,pbCommandBuffer,1,0);
		
	}
}

void *vfnThreadIncrement(void *pvMessageQueue)
{

	mqd_t * IncrementMessageQueue = (mqd_t*)pvMessageQueue;
	char * pbRxBuffer = (char *)malloc(COMMAND_BUFFER_SIZE);
	uint32_t dwCounter = 0;
	int32_t RxStatus;
	
	printf("Increment Message Queue ID: %d\n", *IncrementMessageQueue);

	while(1)
	{
		
		/* Waits for a message. The Thread will block until there's a
		 * message */
		RxStatus = mq_receive(*IncrementMessageQueue,pbRxBuffer,COMMAND_BUFFER_SIZE,NULL);
		if(RxStatus > 0)
		{
			if(*pbRxBuffer  == INCREMENT_COMMAND)
			{
				dwCounter++;
				printf("Incrementing Counter: %d\n",dwCounter);
			}
			else
			{
				printf("Wrong Command\n");
			}
		}
		else
		{
			perror("ReadMSG");
		}
	}
}
