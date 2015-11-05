CC = gcc
CFLAGS = -Wall -Werror
SRCS = uart_echo.c
OUT = uart_echo.out

all:
	$(CC) $(SRCS) $(CFLAGS) -o $(OUT)

clean:
	rm -f $(OUT)

fresh:
	make clean
	make all
