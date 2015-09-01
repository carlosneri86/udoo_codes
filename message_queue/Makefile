CC = gcc
CCFLAGS = -lpthread -lrt -Wall -Werror -o
SRCS = message_queue_sample.c
OUT = message_queue_sample.out

all:
	$(CC) $(SRCS) $(CCFLAGS) $(OUT)

clean:
	rm -f $(OUT)

fresh:
	make clean
	make all

