CC = gcc
CCFLAGS = -Wall -Werror 
SRCS = message_queue_sample.c
OUT = message_queue_sample.out
LIBS = -lpthread -lrt
all:
	$(CC) $(SRCS) $(CCFLAGS) $(LIBS) -o $(OUT)

clean:
	rm -f $(OUT)

fresh:
	make clean
	make all

