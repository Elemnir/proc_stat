CC=gcc

all: test

test: test.c proc_stat.h
	$(CC) -Wall -o test test.c
