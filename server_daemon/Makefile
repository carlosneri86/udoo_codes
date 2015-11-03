CC = gcc
CFLAGS = -Wall -Werror
SRCS = server_daemon.c
OUT = server_daemon.out
LIBS = -lpthread
all:
	$(CC) $(SRCS) $(CFLAGS) $(LIBS) -o $(OUT)

clean:
	rm -f $(OUT)

fresh:
	make clean
	make all
