CC = gcc
CFLAGS = -Wall -Werror
OUTPUT = create_multiple_threads.out
SOURCES = create_multiple_threads.c
LIBS = -lpthread

all:
	$(CC) $(CFLAGS) $(SOURCES) $(LIBS) -o $(OUTPUT)

clean:
	rm -f $(OUTPUT)

fresh: clean all
