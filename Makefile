CFLAGS = -std=c11 -Wall -pedantic -W -Wno-missing-field-initializers -O2 -fPIC -I.
LDFLAGS = -shared
TARGET = libpeg-lite.so

.PHONY: all
all: $(TARGET) test

.PHONY: test
	cd test && $(MAKE)

$(TARGET): $(patsubst %.c,%.o,$(wildcard *.c))
	$(CC) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o$@

.PHONY: clean
clean:
	rm -f $(TARGET) *.o
