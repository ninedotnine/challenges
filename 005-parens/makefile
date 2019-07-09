CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -g -pedantic -O3
FILES = parens.c
OUT_EXE = bin/parens

build:
	mkdir -p bin
	$(CC) $(CFLAGS) $(DEBUGFLAGS) $(INCLUDES) -o $(OUT_EXE) $(FILES) $(LIBS)

clean:
	rm -f $(OUT_EXE)
