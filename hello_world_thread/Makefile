CC = gcc
CFLAGS = -Wall -Werror
OUTPUT = hello_world_thread.out
SOURCES = hello_world_thread.c
LIBS = -lpthread

all:
	$(CC) $(CFLAGS) $(SOURCES) $(LIBS) -o $(OUTPUT)

clean:
	rm -f $(OUTPUT)

fresh: clean all
