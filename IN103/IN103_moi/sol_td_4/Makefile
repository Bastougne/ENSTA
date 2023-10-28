CC = gcc
CFLAGS = -Wall -Werror -Wfatal-errors

DEPS = decode.c encode.c hufftree.c code.c

all: huff_full

huff_full: huff_full.c $(DEPS)
	$(CC) $(CFLAGS) -o huff $(DEPS) huff_full.c

clean:
	$(RM) huff 
