CC = gcc
CFLAGS = -Wall -Werror
SRCS = led_example.c
OUT = led_example.out

all:
	$(CC) $(SRCS) $(CFLAGS) -o $(OUT)

clean:
	rm -f $(OUT)

fresh:
	make clean
	make all
