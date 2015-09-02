#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*Function used for the threads*/
void *vfnThreadPrint(void *pvThreadMutex);

void *vfnThreadIncrement(void *pvThreadMutex);

volatile uint32_t gdwCounter = 0;


int main(void)
{
	pthread_t ThreadPrint;
	pthread_t ThreadIncrement;
	pthread_mutex_t * pMutex;  
	int32_t dwThreadPrintID;
	int32_t dwThreadIncrementID;

	pMutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));

	/* Initialize the mutex */
	pthread_mutex_init(pMutex, NULL);
	/* Create independent threads each of which will execute function */
	dwThreadPrintID = pthread_create(&ThreadPrint, NULL, vfnThreadPrint, (void*)&pMutex);
	
	dwThreadIncrementID = pthread_create(&ThreadIncrement, NULL, vfnThreadIncrement, (void*)&pMutex);
			
	(void)dwThreadPrintID;
	(void)dwThreadIncrementID ;

	/* Wait till threads are complete before main continues. Unless we  */
	/* wait we run the risk of executing an exit which will terminate   */
 	/* the process and all threads before the threads have completed.   */
	while(1)
	{
	}

     
     exit(0);
}

void *vfnThreadPrint(void *pvThreadMutex)
{
	pthread_mutex_t * PrintMutex = (pthread_mutex_t*)pvThreadMutex;
	
	while(1)
	{
		printf("%d\n\r",gdwCounter);
		pthread_mutex_unlock(PrintMutex);
	}
}

void *vfnThreadIncrement(void *pvThreadMutex)
{
	pthread_mutex_t * IncrementMutex = (pthread_mutex_t*)pvThreadMutex;

	while(1)
	{
		pthread_mutex_lock(IncrementMutex);		
		gdwCounter++;
	}
}

