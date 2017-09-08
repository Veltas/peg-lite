CFLAGS = -std=c11 -Wall -pedantic -W -O2 -fPIC
LDFLAGS = $(CFLAGS) -shared -Wl,-soname,libpeg-lite.so.0

libpeg-lite.so.0.0.1: $(wildcard *.c)
