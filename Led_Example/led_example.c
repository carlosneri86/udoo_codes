#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>

int main (void)
{
	int32_t DirectionFile;
	int32_t ValueFile;


	DirectionFile = open("/sys/class/gpio/gpio21/direction", O_WRONLY);

	write(DirectionFile, "out", 3);

	ValueFile = open("/sys/class/gpio/gpio21/value", O_WRONLY);


	while(1)
	{

		write(ValueFile, "1", 1);

		usleep(500000);
		
		write(ValueFile, "0", 1);

		usleep(500000);
	}


	return(0);
}
