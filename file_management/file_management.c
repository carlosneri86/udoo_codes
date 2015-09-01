#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define FILE_BUFFER_SIZE	(100)

int main (void)
{
	int fd_file;
	size_t StringSize;
	int CloseFile;
	char * pbFileBuffer = (char*)malloc(FILE_BUFFER_SIZE);

	/*Creates a file as Write only, on append mode with write permissions*/
	 fd_file = open("test_file.txt", O_WRONLY|O_CREAT|O_APPEND,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);


	for(;;)
	{
		/* read data from stdin */
		/* fgets is blocking and exists at when an "enter" is detected*/
		printf("String to write:\n");
		fgets(pbFileBuffer,FILE_BUFFER_SIZE,stdin);

		/* look for the key word */
		CloseFile = strncmp(pbFileBuffer,"Close",5);

		/* In case the key word is written, close the file */
		if(CloseFile == 0)
		{
			close(fd_file);
			return(0);
		
		}
		
		CloseFile = 0;
		/* get the string size and write it to the file*/
		StringSize = strlen(pbFileBuffer);	

		write(fd_file,pbFileBuffer,StringSize);

	}		


	close(fd_file);
	return(0);
}
