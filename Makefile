CFLAGS = -std=c11 -Wall -pedantic -W -Wno-missing-field-initializers -O2 -fPIC -I.
LDFLAGS = -shared -Wl,-soname,libpeg-lite.so.0

OUT = libpeg-lite.so.0.0.1

$(OUT): $(patsubst %.c,%.o,$(wildcard *.c))
	$(CC) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o$@

.PHONY: clean
clean:
	rm -f $(OUT) *.o
