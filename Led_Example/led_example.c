#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>

int main (void)
{
	int32_t dwDirectionFile;
	int32_t dwValueFile;


	dwDirectionFile = open("/sys/class/gpio/gpio21/direction", O_WRONLY);

	write(dwDirectionFile, "out", 3);

	dwValueFile = open("/sys/class/gpio/gpio21/value", O_WRONLY);


	while(1)
	{

		write(dwValueFile, "1", 1);

		usleep(500000);
		
		write(dwValueFile, "0", 1);

		usleep(500000);
	}


	return(0);
}
