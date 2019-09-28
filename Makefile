CC=gcc

all: main.c split.c split.h
	$(CC) -o main main.c split.c

