CC = gcc
CCFLAGS = -Wall -lpthread -o
SRCS = thread_mutex.c
OUT = thread_mutex.out

all:
	$(CC) $(SRCS) $(CCFLAGS) $(OUT)

clean:
	rm $(OUT)

fresh:
	make clean
	make all
