CC = gcc
CCFLAGS = -Wall -Werror -o
SRCS = alsa_record.c wav_builder.c
OUT = alsa_record.out
LIBS = -lasound

all:
	$(CC) $(SRCS) $(LIBS) $(CCFLAGS) $(OUT)

clean:
	rm -f $(OUT) audio_mic.wav

fresh:
	make clean
	make all
