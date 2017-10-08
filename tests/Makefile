# PROFILING = -pg -fprofile-arcs -ftest-coverage
C_WARN = -Wall -pedantic -W -Wno-missing-field-initializers
CFLAGS = -std=c11 $(C_WARN) -O0 -I.. -g $(PROFILING)
CC = gcc

TARGETS := $(patsubst %.c,%,$(wildcard *.c))

.PHONY: all
all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $^
	@echo Running test: $@
	@valgrind --quiet --error-exitcode=1 --leak-check=full ./$@ || \
	  { echo ":::: $@ failed ::::"; rm $@; exit 1; } ; \

.PHONY: clean
clean:
	rm -f gmon.out *.gcov *.gcda *.gcno $(TARGETS)

set_test: ../set.c ../xarray.c

xarray_test: ../xarray.c

stack_alloc_test: ../stack_alloc.c
