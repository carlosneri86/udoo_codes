CC = gcc
CFLAGS = -Wall -Werror
SRCS = client_echo.c
OUT = client_echo.out

all:
	$(CC) $(SRCS) $(CFLAGS) -o $(OUT)

clean:
	rm -f $(OUT)

fresh:
	make clean
	make all
