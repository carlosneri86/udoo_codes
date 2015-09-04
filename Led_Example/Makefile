CC = gcc
CCFLAGS = -Wall -Werror -o
SRCS = led_example.c
OUT = led_example.out

all:
	$(CC) $(SRCS) $(CCFLAGS) $(OUT)

clean:
	rm -f $(OUT)

fresh:
	make clean
	make all
