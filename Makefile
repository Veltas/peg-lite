CC = gcc
CFLAGS = -std=c11 -Wall -pedantic -W -Wno-missing-field-initializers -O2 -fPIC -I.
LDFLAGS = -shared
TARGET = libpeg-lite.so

.PHONY: all
all: test dist

.PHONY: test
test:
	cd tests && $(MAKE)

.PHONY: dist
dist: $(TARGET)

$(TARGET): $(patsubst %.c,%.o,$(wildcard *.c))
	$(CC) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o$@

.PHONY: clean
clean:
	rm -f $(TARGET) *.o
	cd tests && $(MAKE) clean
