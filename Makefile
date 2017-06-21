CC=gcc

all: test

test: test.c proc_stat.h
	$(CC) -o test test.c
