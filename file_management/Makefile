CC = gcc
CCFLAGS = -Wall -Werror -o
SRCS = file_management.c
OUT = file_management.out

all:
	$(CC) $(SRCS) $(CCFLAGS) $(OUT)

clean:
	rm -f $(OUT)

fresh:
	make clean
	make all
