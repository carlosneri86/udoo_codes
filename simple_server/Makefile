CC = gcc
CFLAGS = -Wall -Werror
SRCS = simple_server.c
OUT = simple_server.out

all:
	$(CC) $(SRCS) $(CFLAGS) -o $(OUT)

clean:
	rm -f $(OUT)

fresh:
	make clean
	make all
