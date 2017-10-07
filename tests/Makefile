# PROFILING = -pg -fprofile-arcs -ftest-coverage
CFLAGS = -std=c11 -Wall -W -pedantic -O0 -I.. -g $(PROFILING)
CC = gcc

TARGETS := $(patsubst %.c,%,$(wildcard *.c))

.PHONY: all
all: $(TARGETS)
	for test in $(TARGETS); do {\
		valgrind --error-exitcode=1 --leak-check=full ./$$test || \
			{ echo ":::: $$test failed ::::"; exit 1; } ; \
	}; done

%: %.c
	$(CC) $(CFLAGS) -o $@ $^

set_test: ../set.c ../xarray.c

xarray_test: ../xarray.c

stack_alloc_test: ../stack_alloc.c

.PHONY: clean
clean:
	rm -f gmon.out *.gcov *.gcda *.gcno $(TARGETS)
