CFLAGS = -std=c11 -Wall -W -pedantic -O0 -I.. -pg -g -fprofile-arcs -ftest-coverage
CC = gcc

set_test: set_test.c ../set.c ../xarray.c
	$(CC) $(CFLAGS) -o $@ $^
