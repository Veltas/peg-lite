CC = gcc
CFLAGS = -std=c11 -Wall -pedantic -W -O3
LDFLAGS = $(CFLAGS)

libpeg-lite.so: peg-lite.c
  $(CC) $(LDFLAGS) $^ -o $@
