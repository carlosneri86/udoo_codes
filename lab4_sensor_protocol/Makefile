CC = gcc
CFLAGS = -Wall -Werror
SRCS = ClienteShellPractica.c
OUT = SensorShell.out
LIBS = -lpthread -lrt -lreadline
all:
	$(CC) $(SRCS) $(CFLAGS) $(LIBS) -o $(OUT)

clean:
	rm -f $(OUT)

fresh:
	make clean
	make all
