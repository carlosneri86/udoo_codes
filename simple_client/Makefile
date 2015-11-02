CC = gcc
CFLAGS = -Wall -Werror
SRCS = simple_client.c
OUT = simple_client.out

all:
	$(CC) $(SRCS) $(CFLAGS) -o $(OUT)

clean:
	rm -f $(OUT)

fresh:
	make clean
	make all
