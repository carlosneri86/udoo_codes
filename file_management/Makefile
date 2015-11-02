CC = gcc
CFLAGS = -Wall -Werror
SRCS = file_management.c
OUT = file_management.out

all:
	$(CC) $(SRCS) $(CFLAGS) -o $(OUT)

clean:
	rm -f $(OUT)

fresh:
	make clean
	make all
