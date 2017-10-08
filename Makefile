CC      = gcc
C_OPT   = -O3 -flto
C_WARN  = -Wall -pedantic -W -Wno-missing-field-initializers
CFLAGS  = -std=c11 $(C_WARN) $(C_OPT) -fPIC -I.
LDFLAGS = $(CFLAGS) -shared
TARGET  = libpeg-lite.so

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
