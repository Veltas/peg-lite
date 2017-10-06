PROFILING = #-pg -fprofile-arcs -ftest-coverage
CFLAGS = -std=c11 -Wall -W -pedantic -Ofast -march=native -I.. -g $(PROFILING)
CC = gcc

set_test: set_test.c ../set.c ../xarray.c
	$(CC) $(CFLAGS) -o $@ $^
