CC = gcc
CFLAGS = -Wall -Werror
SRCS = thread_mutex.c
OUT = thread_mutex.out
LIBS = -lpthread

all:
	$(CC) $(SRCS) $(LIBS) $(CFLAGS) -o $(OUT)

clean:
	rm -f $(OUT)

fresh:
	make clean
	make all
